#include <audio/mixer/MixControls.hpp>

#include <audio/core/ChannelFormat.hpp>
#include <audio/fader/FaderControl.hpp>
#include <audio/mixer/BusControls.hpp>
#include <audio/mixer/MixControlIds.hpp>
#include <audio/mixer/BalanceControl.hpp>
#include <audio/mixer/FrontRearControl.hpp>
#include <audio/mixer/PanControl.hpp>
#include <audio/mixer/MixerControls.hpp>
#include <audio/mixer/MixerControlsIds.hpp>
#include <control/ControlRow.hpp>
#include <control/Control.hpp>
#include <control/EnumControl.hpp>
#include <control/BooleanControl.hpp>

#include <cmath>

using namespace ctoot::audio::mixer;
using namespace ctoot::audio::core;
using namespace ctoot::audio::fader;
using namespace ctoot::control;

using namespace std;

MixControls::MixControls(MixerControls* mixerControls, int stripId, shared_ptr<BusControls> busControls, bool master)
	: AudioControls(busControls->getId(), busControls->getName(), -1)
{
	this->mixerControls = mixerControls;
	this->busControls = busControls;
	this->master = master;
	gainControl = shared_ptr<FaderControl>(mixerControls->createFaderControl(false));
	auto busId = busControls->getId();
	auto format = getChannelFormat();
	channelCount = format->getCount();

	if (channelCount > 1) {
		if (stripId == MixerControlsIds::CHANNEL_STRIP) {
			lcrControl = make_shared<PanControl>();
			add(lcrControl);
		}
		else {
			lcrControl = make_shared<BalanceControl>();
			add(lcrControl);
		}
		derive(lcrControl.get());
	}

	auto enables = make_shared<ControlRow>();

	muteControl = shared_ptr<BooleanControl>(createMuteControl());
	enables->add(muteControl);
	derive(muteControl.get());
	add(enables);

	auto muted = ((busId == MixerControlsIds::AUX_BUS || busId == MixerControlsIds::FX_BUS) && !master);
	gainControl = shared_ptr<FaderControl>(mixerControls->createFaderControl(muted));
	add(gainControl);
	derive(gainControl.get());
}

MixerControls* MixControls::getMixerControls() {
	return mixerControls;
}

float& MixControls::HALF_ROOT_TWO()
{
	return HALF_ROOT_TWO_;
}
float MixControls::HALF_ROOT_TWO_ = static_cast< float >((sqrt(2) / 2));

void MixControls::derive(Control* c)
{
	switch (c->getId()) {
	case MixControlIds::MUTE:
		mute = muteControl->getValue();
		break;
	case MixControlIds::SOLO:
		solo = soloControl->getValue();
		break;
	case MixControlIds::GAIN:
		gain = gainControl->getGain();
		break;
	case MixControlIds::LCR:
		left = lcrControl->getLeft();
		right = lcrControl->getRight();
		break;
	}
}


bool MixControls::isMaster()
{
    return master;
}


shared_ptr<ChannelFormat> MixControls::getChannelFormat()
{
    return busControls->getChannelFormat();
}

bool MixControls::isMute()
{
    return mute;
}

bool MixControls::isEnabled()
{
	return !isMute();
}

float MixControls::getGain()
{
    return gain;
}

void MixControls::getChannelGains(vector<float>* dest)
{
	float r;
	float f;
	switch (channelCount) {
	case 6:
		//dest[5] = gain;
		//dest[4] = gain;
	case 4:
		r = gain * rear;
		//dest[3] = r * right;
		//dest[2] = r * left;
		f = gain * front;
		//dest[1] = f * right;
		//dest[0] = f * left;
		break;
	case 2:
		(*dest)[1] = gain * right;
		(*dest)[0] = gain * left;
		break;
	case 1:
		//dest[0] = gain;
		break;
	}
}

float MixControls::getSmoothingFactor()
{
    return mixerControls->getSmoothingFactor();
}

EnumControl* MixControls::createRouteControl(int stripId)
{
	return nullptr;
}


BooleanControl* MixControls::createMuteControl()
{
    auto c = new BooleanControl(MixControlIds::MUTE, "Mute", false);
	string name = c->getName();
	name = name.substr(0, 1);
    c->setAnnotation(name);
    return c;
}

string MixControls::getName()
{
    return Control::getName();
}
