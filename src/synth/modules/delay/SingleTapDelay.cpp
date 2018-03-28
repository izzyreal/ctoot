#include <synth/modules/delay/SingleTapDelay.hpp>

using namespace ctoot::synth::modules::delay;
using namespace std;

SingleTapDelay::SingleTapDelay(int32_t ntaps)
{
    delayLine = vector<float>(ntaps);
	for (int i = 0; i < delayLine.size(); i++)
		delayLine[i] = 0;
	this->ntaps = ntaps;
	delaySamples = ntaps / 2;
    wrpos = delaySamples;
}

float ctoot::synth::modules::delay::SingleTapDelay::getSample(float in)
{
    delayLine[wrpos] = in;
    wrpos += 1;
    wrpos %= ntaps;
    rdpos += 1;
    rdpos %= ntaps;
    return delayLine[rdpos];
}
