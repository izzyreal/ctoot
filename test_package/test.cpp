#include <stdio.h>
#include "Logger.hpp"
#include "audio/core/AudioFormat.hpp"

#include <string>

int main() {
    moduru::Logger::l.setPath("moduru.log");
    moduru::Logger::l.log("Yay!");
    auto af = new ctoot::audio::core::AudioFormat(44100, 16, 2, true, false);
    printf("Moduru test successful\n");
    printf("AudioFormat sample rate: %i\n", (int)(af->getSampleRate()));
    if (af->getSampleRate() == 44100) {
        printf("ctoot test successful\n");
    } else {
        printf("ctoot test failed\n");
    }
    delete af;
    return 0;
}
