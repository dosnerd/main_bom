#include <iostream>
#include <AssembleConnection.h>
#include <Bom.h>
#include <thread>
#include <alsa/asoundlib.h>
#include <cmath>

#define CHANNELS            1
#define SAMPLE_RATE         8000
#define FRAME_PER_PERIOD    1024
#define SAMPLE_SIZE         1
#define BUFFER_SIZE         (FRAME_PER_PERIOD * SAMPLE_SIZE * CHANNELS)

int main() {
    std::string device = "default";
    float buffer[BUFFER_SIZE] = {0};

    int err;
    unsigned int i, j;
    snd_pcm_t *handle;
    snd_pcm_sframes_t frames;

    if ((err = snd_pcm_open(&handle, device.c_str(), SND_PCM_STREAM_PLAYBACK, 0)) < 0) {
        printf("Playback open error: %s\n", snd_strerror(err));
        exit(EXIT_FAILURE);
    }

    if ((err = snd_pcm_set_params(handle,
                                  SND_PCM_FORMAT_FLOAT,
                                  SND_PCM_ACCESS_RW_INTERLEAVED,
                                  CHANNELS,
                                  SAMPLE_RATE,
                                  true,
                                  500000)) < 0) {   /* 0.5sec */
        printf("Playback open error: %s\n", snd_strerror(err));
        exit(EXIT_FAILURE);
    }

    for (i = 0;; i++) {
        for (j = 0; j < BUFFER_SIZE; j++) {
            if ((i & 0x07) == 0x07) {
                buffer[j] = sin(2 * M_PI * j / SAMPLE_RATE * 2000);
            } else {
                buffer[j] = 0;
            }

        }

        frames = snd_pcm_writei(handle, buffer, FRAME_PER_PERIOD * SAMPLE_SIZE * CHANNELS);
        if (frames < 0)
            frames = snd_pcm_recover(handle, frames, 0);
        if (frames < 0) {
            printf("snd_pcm_writei failed: %s\n", snd_strerror(frames));
            break;
        }
        if (frames > 0 && frames < BUFFER_SIZE)
            printf("Short write (expected %i, wrote %li)\n", BUFFER_SIZE, frames);
    }

    snd_pcm_close(handle);

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