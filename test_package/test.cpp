#include <stdio.h>
#include "Logger.hpp"
#include <audio/core/AudioFormat.hpp>

int main() {
    moduru::Logger::l.setPath("moduru.log");
    printf("moduru included and linked correctly to ctoot\n");
	ctoot::audio::core::AudioFormat(44100.f, 16, 2, true, true);
	printf("ctoot package ok");
}
