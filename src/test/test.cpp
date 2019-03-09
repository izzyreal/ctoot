#include "../main/audio/core/AudioFormat.hpp"

int main(){
	auto af = new ctoot::audio::core::AudioFormat(44100, 16, 2, false, false);
	float sr = af->getSampleRate();
	printf("Samplerate is %f\n", sr);
	delete af;
	printf("ctoot test successful\n");
}