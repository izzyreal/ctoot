#include <audio/meter/MeterControls.hpp>

#include <audio/core/ChannelFormat.hpp>
#include <audio/meter/MeterIndicator.hpp>
#include <audio/meter/MindBControl.hpp>
#include <audio/meter/OverIndicator.hpp>
#include <audio/meter/ResetControl.hpp>
#include <audio/meter/TypeControl.hpp>
#include <control/Control.hpp>
#include <control/LinearLaw.hpp>

using namespace ctoot::audio::meter;
using namespace std;

constexpr int ctoot::audio::meter::MeterControls::METER;
constexpr int ctoot::audio::meter::MeterControls::METER_TYPE;
constexpr int ctoot::audio::meter::MeterControls::METER_RESET;
constexpr int ctoot::audio::meter::MeterControls::METER_OVERS;
constexpr int ctoot::audio::meter::MeterControls::METER_INDICATOR;
constexpr int ctoot::audio::meter::MeterControls::METER_MIN_DB;

weak_ptr<ctoot::control::LinearLaw> ctoot::audio::meter::MeterControls::METER_LAW()
{
	static auto res = make_shared<ctoot::control::LinearLaw>(-60.0f, 20.0f, "dB");
    return res;
}

MeterControls::MeterControls(std::weak_ptr<ctoot::audio::core::ChannelFormat> format, string name)
	: MeterControls(format, name, true)
{
}

MeterControls::MeterControls(std::weak_ptr<ctoot::audio::core::ChannelFormat> format, string name, bool full)
	: ctoot::audio::core::AudioControls(METER, name)
{
	channelFormat = format;
	auto nchannels = channelFormat.lock()->getCount();
	channelState = vector<ChannelState>(nchannels);

	if (full) {
		add(std::move(make_shared<ResetControl>(this)));
		add(std::move(make_shared<OverIndicator>()));
		auto tc = make_shared<TypeControl>();
		typeControl = tc;
		add(std::move(tc));
	}
	add(std::move(make_shared<MeterIndicator>(name)));
	if (full) {
		auto mdbc = make_shared<MindBControl>();
		mindBControl = mdbc;
		add(std::move(mdbc));
		derive(typeControl.lock().get());
		derive(mindBControl.lock().get());
	}
}

void ctoot::audio::meter::MeterControls::derive(ctoot::control::Control* c)
{
	switch (c->getId()) {
	case METER_TYPE:
		maxdB = typeControl.lock()->getMaxdB();
		break;
	case METER_MIN_DB:
		mindB = mindBControl.lock()->getMindB();
		break;
	}
}

bool ctoot::audio::meter::MeterControls::canBypass()
{
    return false;
}

bool ctoot::audio::meter::MeterControls::isAlwaysVertical()
{
    return true;
}

float ctoot::audio::meter::MeterControls::getMaxdB()
{
    return maxdB;
}

float ctoot::audio::meter::MeterControls::getMindB()
{
    return mindB;
}

weak_ptr<ctoot::audio::core::ChannelFormat> ctoot::audio::meter::MeterControls::getChannelFormat()
{
    return channelFormat;
}

bool ctoot::audio::meter::MeterControls::invalidChannel(int chan)
{
    return chan < 0 || chan >= channelFormat.lock()->getCount();
}

ChannelState ctoot::audio::meter::MeterControls::getState(int chan)
{
	if (invalidChannel(chan))
		return {};

	return channelState[chan];
}

void ctoot::audio::meter::MeterControls::resetOvers()
{
    for (int c = 0; c < channelFormat.lock()->getCount(); c++) {
        channelState[c].overs = 0;
    }
}

void ctoot::audio::meter::MeterControls::resetMaxima()
{
    for (int c = 0; c < channelFormat.lock()->getCount(); c++) {
        channelState[c].maxPeak = channelState[c].peak;
        channelState[c].maxAverage = channelState[c].average;
    }
}

void ctoot::audio::meter::MeterControls::addOvers(int chan, int overs)
{
	if (invalidChannel(chan) || overs == 0)
		return;

	channelState[chan].overs += overs;
}

void ctoot::audio::meter::MeterControls::setPeak(int chan, float peak)
{
	if (invalidChannel(chan))
		return;

	auto state = channelState[chan];
	if (peak > state.peak) {
		state.peak = peak;
	}
	else {
		state.peak += peakRelease * (peak - state.peak);
	}
	if (state.peak > state.maxPeak) {
		state.maxPeak = state.peak;
	}
}

void ctoot::audio::meter::MeterControls::setAverage(int chan, float average)
{
	if (invalidChannel(chan))
		return;

	auto state = channelState[chan];
	if (average != average)
		average = 0;

	state.average += averageSmooth * (average - state.average);
	if (state.average > state.maxAverage) {
		state.maxAverage = state.average;
	}
}

double ctoot::audio::meter::MeterControls::PEAK_K_PER_MS()
{
    return PEAK_K_PER_MS_;
}
double ctoot::audio::meter::MeterControls::PEAK_K_PER_MS_ = log(0.05) / 3000.0;

double ctoot::audio::meter::MeterControls::AV_K_PER_MS()
{
    return AV_K_PER_MS_;
}
double ctoot::audio::meter::MeterControls::AV_K_PER_MS_ = log(0.01) / 600;


void ctoot::audio::meter::MeterControls::setUpdateTime(float ms)
{
	peakRelease = static_cast<float>((1.0 - exp(ms * PEAK_K_PER_MS_)));
	averageSmooth = static_cast<float>((1.0 - exp(ms * AV_K_PER_MS_)));
}
