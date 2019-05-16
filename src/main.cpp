#include <iostream>
#include <AssembleConnection.h>
#include <Bom.h>
#include <thread>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sound/asound.h>
#include <cstring>

#define BUFFER_SIZE         8192

void dump_info(struct snd_pcm_info *info) {
    std::cout << "Device: " << info->device << std::endl;
    std::cout << "Subdevice: " << info->subdevice << std::endl;
    std::cout << "Stream: " << info->stream << std::endl;
    std::cout << "Card: " << info->card << std::endl;
    std::cout << "Id: " << info->id << std::endl;
    std::cout << "Name: " << info->name << std::endl;
    std::cout << "Subname: " << info->subname << std::endl;
    std::cout << "dev_class: " << info->dev_class << std::endl;
    std::cout << "subdevices_count: " << info->subdevices_count << std::endl;
    std::cout << "subdevices_avail: " << info->subdevices_avail << std::endl;
    std::cout << std::string(12, '-') << std::endl;
}

void init_hw_param_struct(struct snd_pcm_hw_params *params) {
    int i;
    for (i = SNDRV_PCM_HW_PARAM_FIRST_MASK; i < SNDRV_PCM_HW_PARAM_LAST_MASK; ++i) {
        struct snd_mask *mask = &params->masks[i - SNDRV_PCM_HW_PARAM_FIRST_MASK];
        mask->bits[0] = ~0u;
        mask->bits[1] = ~0u;
    }

    for (i = SNDRV_PCM_HW_PARAM_FIRST_INTERVAL; i < SNDRV_PCM_HW_PARAM_LAST_INTERVAL; ++i) {
        struct snd_interval *interval = &params->intervals[i - SNDRV_PCM_HW_PARAM_FIRST_INTERVAL];
        interval->min = 0;
        interval->max = ~0u;
    }
}

void param_set_mask(struct snd_pcm_hw_params *params, int maskNumber, unsigned bit) {
    struct snd_mask *mask = &params->masks[maskNumber - SNDRV_PCM_HW_PARAM_FIRST_MASK];
    if (bit > SNDRV_MASK_MAX)
        return;

    mask->bits[0] = 0;
    mask->bits[1] = 0;
    mask->bits[bit >> 5u] |= (1u << (bit & 31u));
}

void param_set_interval(struct snd_pcm_hw_params *params, int intervalNumber, unsigned value) {
    struct snd_interval *interval = &params->intervals[intervalNumber - SNDRV_PCM_HW_PARAM_FIRST_INTERVAL];
    interval->min = value;
    interval->max = value;
    interval->integer = 1;
}

void param_set_interval_min(struct snd_pcm_hw_params *params, int intervalNumber, unsigned value) {
    struct snd_interval *interval = &params->intervals[intervalNumber - SNDRV_PCM_HW_PARAM_FIRST_INTERVAL];
    interval->min = value;
    interval->max = value;
    interval->integer = 1;
}

bool init_hw_params(int fd) {
    struct snd_pcm_hw_params params = {0};

    init_hw_param_struct(&params);

    param_set_mask(&params, SNDRV_PCM_HW_PARAM_ACCESS, SNDRV_PCM_ACCESS_RW_INTERLEAVED);
    param_set_mask(&params, SNDRV_PCM_HW_PARAM_FORMAT, SNDRV_PCM_FORMAT_S16_LE);
    param_set_mask(&params, SNDRV_PCM_HW_PARAM_SUBFORMAT, SNDRV_PCM_SUBFORMAT_STD);

    param_set_interval_min(&params, SNDRV_PCM_HW_PARAM_BUFFER_BYTES, BUFFER_SIZE);
    param_set_interval(&params, SNDRV_PCM_HW_PARAM_SAMPLE_BITS, 16);
    param_set_interval(&params, SNDRV_PCM_HW_PARAM_FRAME_BITS, 16);
    param_set_interval(&params, SNDRV_PCM_HW_PARAM_CHANNELS, 2);
    param_set_interval(&params, SNDRV_PCM_HW_PARAM_PERIODS, 2);
    param_set_interval(&params, SNDRV_PCM_HW_PARAM_RATE, 44100);

    if (ioctl(fd, SNDRV_PCM_IOCTL_HW_PARAMS, &params)) {
        std::cerr << "Unable to set hw params" << std::endl
                  << strerror(errno) << " (" << errno << ")" << std::endl;
        return false;
    }
    return true;
}

bool init_sw_params(int fd) {
    struct snd_pcm_sw_params params = {0};

    params.tstamp_mode = SNDRV_PCM_TSTAMP_NONE;
    params.period_step = 1;
    params.avail_min = 1;
    params.start_threshold = BUFFER_SIZE / 4;
    params.stop_threshold = BUFFER_SIZE / 4;
    params.xfer_align = BUFFER_SIZE / 8;
    params.silence_size = 0;
    params.silence_threshold = 0;

    if (ioctl(fd, SNDRV_PCM_IOCTL_SW_PARAMS, &params)) {
        std::cerr << "Unable to set sw params" << std::endl
                  << strerror(errno) << " (" << errno << ")" << std::endl;
        return false;
    }

    return true;
}

int main() {
    int fd = open("/dev/snd/pcmC0D0p", O_RDWR);
    struct snd_pcm_info info;

    if (fd < -1) {
        std::cerr << "Failed to open sound driver" << std::endl;
        return 1;
    }

    if (ioctl(fd, SNDRV_PCM_IOCTL_INFO, &info)) {
        std::cerr << "Failed to retrieve info" << std::endl;
        return 1;
    }
    dump_info(&info);


    if (!init_sw_params(fd))
        return 1;

//    for (unsigned i = 0; i < 1000000; ++i) {
//        file << (i * ((i >> 12u | i >> 8u) & 63u & i >> 4u));
//    }
    std::cout << "Done" << std::endl;




//    Bom bom;
//    bom.WaitForArmed();
//    bom.WaitForCountdown();
//    bom.CountDown();
//
//    std::cout << "END GAME" << std::endl;
    return 0;
}