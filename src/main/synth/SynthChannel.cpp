#include <synth/SynthChannel.hpp>

#include <audio/core/ChannelFormat.hpp>
//#include <midi/misc/Controller.hpp>
#include <synth/ControlChange.hpp>
#include <cmath>

#include <Logger.hpp>

using namespace ctoot::synth;
using namespace std;

SynthChannel::SynthChannel()
{
}

vector<float>& SynthChannel::freqTable()
{
    static std::vector<float> res;
    if (res.empty()) {
        for (auto i = 0; i < 140; i++) {
            res.push_back(midiFreqImpl(i));
        }
    }
    return res;
}

float SynthChannel::midiFreq(float pitch)
{
	if (pitch < 0)
		return freqTable()[0];

	if (pitch >= (int)(freqTable().size()) - 1)
		return freqTable()[(int)(freqTable().size()) - 2];

	auto idx = (int)(pitch);
	auto frac = pitch - idx;
	return freqTable()[idx] * (1 - frac) + freqTable()[idx + 1] * frac;
}

float SynthChannel::midiFreqImpl(int pitch)
{
	auto res = (float)(440.0 * pow(2.0, ((double)(pitch) - 69.0) / 12.0));
    return res;
}

void SynthChannel::setSampleRate(int rate)
{
    sampleRate = rate;
}

std::weak_ptr<ctoot::audio::core::ChannelFormat> SynthChannel::getChannelFormat()
{
    return ctoot::audio::core::ChannelFormat::MONO();
}

void SynthChannel::noteOff(int pitch, int velocity)
{
    noteOff(pitch);
}

void SynthChannel::controlChange(int arg0, int arg1)
{
	controller[arg0] = static_cast<int8_t>(arg1);
	if (arg0 < 32) controller[arg0 + 32] = 0;

	
	notifyObservers(new ctoot::synth::ControlChange(arg0, arg1));
}

int SynthChannel::getController(int arg0)
{
    return controller[arg0];
}

int SynthChannel::getProgram()
{
    return 0;
}

void SynthChannel::programChange(int arg0)
{
}

void SynthChannel::programChange(int arg0, int arg1)
{
}

void SynthChannel::setMono(bool mono)
{
}

