#include <iostream>
#include <AssembleConnection.h>
#include <Bom.h>
#include <thread>
#include <alsa/asoundlib.h>
#include <cmath>

int main() {
    std::string device = "default";
    unsigned char buffer[16*1024] = { 0 };

    int err;
    unsigned int i;
    snd_pcm_t *handle;
    snd_pcm_sframes_t frames;
    for (i = 0; i < sizeof(buffer); i++)
        buffer[i] = 0;

    if ((err = snd_pcm_open(&handle, device.c_str(), SND_PCM_STREAM_PLAYBACK, 0)) < 0) {
        printf("Playback open error: %s\n", snd_strerror(err));
        exit(EXIT_FAILURE);
    }

    if ((err = snd_pcm_set_params(handle,
                                  SND_PCM_FORMAT_U8,
                                  SND_PCM_ACCESS_RW_INTERLEAVED,
                                  1,
//                                  48000,
                                  8000,
                                  1,
                                  500000)) < 0) {   /* 0.5sec */
        printf("Playback open error: %s\n", snd_strerror(err));
        exit(EXIT_FAILURE);
    }



    for (i = 0; i < 16; i++) {
        frames = snd_pcm_writei(handle, buffer, sizeof(buffer));
        if (frames < 0)
            frames = snd_pcm_recover(handle, frames, 0);
        if (frames < 0) {
            printf("snd_pcm_writei failed: %s\n", snd_strerror(frames));
            break;
        }
        if (frames > 0 && frames < (long)sizeof(buffer))
            printf("Short write (expected %li, wrote %li)\n", (long)sizeof(buffer), frames);
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