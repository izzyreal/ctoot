#include "DynamicsControls.hpp"

#include <dsp/VolumeUtils.hpp>
#include <audio/core/AudioBuffer.hpp>
#include <audio/core/KVolumeUtils.hpp>
#include <audio/core/TapControl.hpp>
#include <audio/dynamics/DynamicsControlIds.hpp>
#include <audio/dynamics/InverseRatioControl.hpp>
#include <audio/dynamics/GainReductionIndicator.hpp>
#include <audio/dynamics/izcompressor/ChannelControl.hpp>
#include <control/BooleanControl.hpp>
#include <control/ControlColumn.hpp>
#include <control/CompoundControl.hpp>
#include <control/Control.hpp>
#include <control/ControlLaw.hpp>
#include <control/FloatControl.hpp>
#include <control/LinearLaw.hpp>
#include <control/LogLaw.hpp>

using namespace ctoot::audio::dynamics;
using namespace ctoot::control;
using namespace std;

weak_ptr<ctoot::control::ControlLaw> DynamicsControls::THRESH_LAW()
{
	static auto res = make_shared<LinearLaw>(-40.0f, 20.0f, "dB");
	return res;
}

weak_ptr<ctoot::control::ControlLaw> DynamicsControls::RATIO_LAW()
{
	static auto res = make_shared<LogLaw>(1.5f, 10.0f, "");
	return res;
}

weak_ptr<ctoot::control::ControlLaw> DynamicsControls::INVERSE_RATIO_LAW()
{
	static auto res = make_shared<LinearLaw>(1, -1, "");
	return res;
}

weak_ptr<ctoot::control::ControlLaw> DynamicsControls::KNEE_LAW()
{
	static auto res = make_shared<LinearLaw>(0.1f, 20.0f, "dB");
	return res;
}

weak_ptr<ctoot::control::ControlLaw> DynamicsControls::ATTACK_LAW()
{
	static auto res = make_shared<LogLaw>(0.1f, 100.0f, "ms");
	return res;
}

weak_ptr<ctoot::control::ControlLaw> DynamicsControls::LOOK_AHEAD_LAW()
{
	static auto res = make_shared<LinearLaw>(0.0f, 15.0f, "ms");
	return res;
}

weak_ptr<ctoot::control::ControlLaw> DynamicsControls::HOLD_LAW()
{
	static auto res = make_shared<LogLaw>(1.0f, 1000.0f, "ms");
	return res;
}

weak_ptr<ctoot::control::ControlLaw> DynamicsControls::RELEASE_LAW()
{
	static auto res = make_shared<LogLaw>(200.0f, 2000.0f, "ms");
	return res;
}

weak_ptr<ctoot::control::ControlLaw> DynamicsControls::DRY_GAIN_LAW()
{
	static auto res = make_shared<LinearLaw>(-80.0f, 20.0f, "dB");
	return res;
}

weak_ptr<ctoot::control::ControlLaw> DynamicsControls::WET_GAIN_LAW()
{
	static auto res = make_shared<LinearLaw>(-80.0f, 20.0f, "dB");
	return res;
}

weak_ptr<ctoot::control::ControlLaw> DynamicsControls::GAIN_LAW()
{
	static auto res = make_shared<LinearLaw>(0.0f, 20.0f, "dB");
	return res;
}

weak_ptr<ctoot::control::ControlLaw> DynamicsControls::INPUT_GAIN_LAW()
{
	static auto res = make_shared<LinearLaw>(-24.0f, 24.0f, "dB");
	return res;
}

weak_ptr<ctoot::control::ControlLaw> DynamicsControls::OUTPUT_GAIN_LAW()
{
	static auto res = make_shared<LinearLaw>(-24.0f, 24.0f, "dB");
	return res;
}

weak_ptr<ctoot::control::ControlLaw> DynamicsControls::DEPTH_LAW()
{
	static auto res = make_shared<LinearLaw>(-80.0f, 0.0f, "dB");
	return res;
}

weak_ptr<ctoot::control::ControlLaw> DynamicsControls::HYSTERESIS_LAW()
{
	static auto res = make_shared<LinearLaw>(0.0f, 20.0f, "dB");
	return res;
}

DynamicsControls::DynamicsControls(int32_t id, std::string name)
	: DynamicsControls(id, name, 0)
{
}

DynamicsControls::DynamicsControls(int32_t id, std::string name, int32_t idOffset)
	: ctoot::audio::core::AudioControls(id, name, 126 - idOffset)
{
	this->idOffset = idOffset;
}

void DynamicsControls::update(float sampleRate)
{
    this->sampleRate = sampleRate;
    deriveAttack();
    deriveHold();
    deriveRelease();
	deriveLookAhead();
}

void DynamicsControls::derive(ctoot::control::Control* c)
{
    switch (c->getId() - idOffset) {
    case DynamicsControlIds::THRESHOLD:
        deriveThreshold();
        break;
    case DynamicsControlIds::RATIO:
        deriveRatio();
        break;
    case DynamicsControlIds::KNEE:
        deriveKnee();
        break;
    case DynamicsControlIds::ATTACK:
        deriveAttack();
        break;
    case DynamicsControlIds::HOLD:
        deriveHold();
        break;
    case DynamicsControlIds::RELEASE:
        deriveRelease();
        break;
    case DynamicsControlIds::DRY_GAIN:
        deriveDryGain();
		break;
	case DynamicsControlIds::WET_GAIN:
		deriveWetGain();
		break;
	case DynamicsControlIds::GAIN:
        deriveGain();
        break;
    case DynamicsControlIds::DEPTH:
        deriveDepth();
        break;
    case DynamicsControlIds::KEY:
        deriveKey();
        break;
    case DynamicsControlIds::HYSTERESIS:
        deriveHysteresis();
        break;
    case DynamicsControlIds::RMS:
        deriveRMS();
        break;
	case DynamicsControlIds::DETECTION_CHANNEL_MODE:
		deriveDetectionChannelMode();
		break;
	case DynamicsControlIds::ATTENUATION_CHANNEL_MODE:
		deriveAttenuationChannelMode();
		break;
	case DynamicsControlIds::INPUT_GAIN:
		deriveInputGain();
		break;
	case DynamicsControlIds::OUTPUT_GAIN:
		deriveOutputGain();
		break;
	case DynamicsControlIds::LOOK_AHEAD:
		deriveLookAhead();
		break;
	case DynamicsControlIds::MUTE:
		deriveMute();
		break;
	}
}

void DynamicsControls::deriveThreshold()
{
	thresholddB = thresholdControl.lock()->getValue();
	//threshold = static_cast<float>(ctoot::audio::core::KVolumeUtils::log2lin(thresholddB));
	threshold = static_cast<float>(ctoot::dsp::VolumeUtils::log2lin(thresholddB));
	inverseThreshold = 1.0f / threshold;
}

void DynamicsControls::deriveInputGain() {
	if (!inputGainControl.lock()) return;
	inputGain = static_cast<float>(ctoot::dsp::VolumeUtils::log2lin(inputGainControl.lock()->getValue()));
}

void DynamicsControls::deriveOutputGain() {
	if (!outputGainControl.lock()) return;
	outputGain = static_cast<float>(ctoot::dsp::VolumeUtils::log2lin(outputGainControl.lock()->getValue()));
}

void DynamicsControls::deriveMute() {
	if (!muteControl.lock()) return;
	mute = muteControl.lock()->getValue();
}

void DynamicsControls::deriveDetectionChannelMode()
{
	if (!detectionChannelControl.lock())
		return;

	detectionChannelMode = boost::any_cast<string>(detectionChannelControl.lock()->getValue());
}

void DynamicsControls::deriveAttenuationChannelMode()
{
	if (!attenuationChannelControl.lock())
		return;

	attenuationChannelMode = boost::any_cast<string>(attenuationChannelControl.lock()->getValue());
}

void DynamicsControls::deriveRatio()
{
	if (!ratioControl.lock())
		return;

	auto val = ratioControl.lock()->getValue();
	inverseRatio = val > 1.0f ? 1.0f / val : val;
}

void DynamicsControls::deriveKnee()
{
	if (!kneeControl.lock())
		return;

	kneedB = kneeControl.lock()->getValue();
}

void DynamicsControls::deriveRMS()
{
    rms = rmsControl.lock()->getValue();
}

float& DynamicsControls::LOG_0_01()
{
	static float res = log(0.01);
	return res;
}

float DynamicsControls::deriveTimeFactor(float milliseconds)
{
	auto ns = milliseconds * sampleRate * 0.001f;
	auto k = LOG_0_01() / ns;
	return static_cast<float>(exp(k));
}

void DynamicsControls::deriveAttack()
{
    attack = deriveTimeFactor(attackControl.lock()->getValue());
}

void DynamicsControls::deriveLookAhead()
{
	if (!lookAheadControl.lock()) return;
	lookAhead = lookAheadControl.lock()->getValue();
}

void DynamicsControls::deriveHold()
{
	if (!holdControl.lock())
		return;

	hold = static_cast<int32_t>(holdControl.lock()->getValue() * sampleRate * 0.001f);
}

void DynamicsControls::deriveRelease()
{
	release = deriveTimeFactor(releaseControl.lock()->getValue());
}

void DynamicsControls::deriveDryGain()
{
	if (!dryGainControl.lock())
		return;

	dryGain = static_cast<float>(ctoot::dsp::VolumeUtils::log2lin(dryGainControl.lock()->getValue()));
}

void DynamicsControls::deriveWetGain()
{
	if (!wetGainControl.lock())
		return;

	wetGain = static_cast<float>(ctoot::dsp::VolumeUtils::log2lin(wetGainControl.lock()->getValue()));
}

void DynamicsControls::deriveGain()
{
	if (!gainControl.lock())
		return;

	gain = static_cast<float>(ctoot::dsp::VolumeUtils::log2lin(gainControl.lock()->getValue()));
}

void DynamicsControls::deriveDepth()
{
	if (!depthControl.lock())
		return;

	depth = static_cast<float>(ctoot::dsp::VolumeUtils::log2lin(depthControl.lock()->getValue()));
}

void DynamicsControls::deriveHysteresis()
{
	hysteresis = static_cast<float>(ctoot::dsp::VolumeUtils::log2lin(-hysteresisControl.lock()->getValue()));
}

void DynamicsControls::deriveKey()
{
	if (!keyControl.lock())
		return;

	key = keyControl.lock()->getBuffer();
}

void DynamicsControls::setParent(ctoot::control::CompoundControl* parent)
{
	AudioControls::setParent(parent);
	if (parent == nullptr && keyControl.lock()) {
		keyControl.lock()->remove();
	}
}

bool DynamicsControls::hasInputGain() {
	return false;
}

bool DynamicsControls::hasOutputGain() {
	return false;
}

bool DynamicsControls::hasMute() {
	return false;
}

bool DynamicsControls::hasGainReductionIndicator()
{
    return false;
}

weak_ptr<ControlLaw> DynamicsControls::getThresholdLaw()
{
	return THRESH_LAW();
}

shared_ptr<ctoot::control::FloatControl> DynamicsControls::createThresholdControl()
{
    auto control = make_shared<ctoot::control::FloatControl>(DynamicsControlIds::THRESHOLD + idOffset, "Threshold", getThresholdLaw(), 0.1f, 0.0f);
    return control;
}

bool DynamicsControls::hasInverseRatio()
{
    return false;
}

bool DynamicsControls::hasRatio()
{
    return false;
}

shared_ptr<ctoot::control::FloatControl> DynamicsControls::createRatioControl()
{
    auto ratio = make_shared<ctoot::control::FloatControl>(DynamicsControlIds::RATIO + idOffset, "Ratio", RATIO_LAW(), 0.1f, 2.0f);
    return ratio;
}

bool DynamicsControls::hasKnee()
{
    return false;
}

shared_ptr<ctoot::control::FloatControl> DynamicsControls::createKneeControl()
{
    auto ratio = make_shared<ctoot::control::FloatControl>(DynamicsControlIds::KNEE + idOffset, "Knee", KNEE_LAW(), 0.1f, 10.0f);
    return ratio;
}

bool DynamicsControls::hasRMS()
{
    return false;
}

shared_ptr<ctoot::control::BooleanControl> DynamicsControls::createRMSControl()
{
    auto c = make_shared<ctoot::control::BooleanControl>(DynamicsControlIds::RMS + idOffset, "RMS", false);
    return c;
}

weak_ptr<ControlLaw> DynamicsControls::getAttackLaw()
{
	return ATTACK_LAW();
}

weak_ptr<ControlLaw> DynamicsControls::getLookAheadLaw()
{
	return LOOK_AHEAD_LAW();
}

shared_ptr<ctoot::control::FloatControl> DynamicsControls::createAttackControl()
{
    return make_shared<ctoot::control::FloatControl>(DynamicsControlIds::ATTACK + idOffset, "Attack", getAttackLaw(), 0.1f, getAttackLaw().lock()->getMinimum());
}

shared_ptr<ctoot::control::FloatControl> DynamicsControls::createLookAheadControl()
{
	return make_shared<ctoot::control::FloatControl>(DynamicsControlIds::LOOK_AHEAD + idOffset, "Look Ahead", getLookAheadLaw(), 0.1f, getLookAheadLaw().lock()->getMinimum());
}

bool DynamicsControls::hasLookAhead()
{
	return false;
}

bool DynamicsControls::hasHold()
{
    return false;
}

weak_ptr<ControlLaw> DynamicsControls::getHoldLaw()
{
	return HOLD_LAW();
}

shared_ptr<ctoot::control::FloatControl> DynamicsControls::createHoldControl()
{
    return make_shared<ctoot::control::FloatControl>(DynamicsControlIds::HOLD + idOffset, "Hold", getHoldLaw(), 1.0f, 10.0f);
}

weak_ptr<ControlLaw> DynamicsControls::getReleaseLaw()
{
	return RELEASE_LAW();
}

shared_ptr<ctoot::control::FloatControl> DynamicsControls::createReleaseControl()
{
    return make_shared<ctoot::control::FloatControl>(DynamicsControlIds::RELEASE + idOffset, "Release", getReleaseLaw(), 1.0f, getReleaseLaw().lock()->getMinimum());
}

bool DynamicsControls::hasDryGain()
{
    return false;
}

bool DynamicsControls::hasWetGain()
{
	return false;
}

weak_ptr<ControlLaw> DynamicsControls::getWetGainLaw()
{
	return WET_GAIN_LAW();
}

weak_ptr<ControlLaw> DynamicsControls::getDryGainLaw()
{
    return DRY_GAIN_LAW();
}

shared_ptr<ctoot::control::FloatControl> DynamicsControls::createDryGainControl()
{
    return make_shared<ctoot::control::FloatControl>(DynamicsControlIds::DRY_GAIN + idOffset, "Dry Gain", getDryGainLaw(), 1.0f, getDryGainLaw().lock()->getMinimum());
}

shared_ptr<ctoot::control::FloatControl> DynamicsControls::createWetGainControl()
{
	return make_shared<ctoot::control::FloatControl>(DynamicsControlIds::WET_GAIN + idOffset, "Wet Gain", getWetGainLaw(), 1.0f, 0);
}

bool DynamicsControls::hasGain()
{
    return false;
}

weak_ptr<ControlLaw> DynamicsControls::getGainLaw()
{
    return GAIN_LAW();
}

shared_ptr<ctoot::control::FloatControl> DynamicsControls::createGainControl()
{
    return make_shared<ctoot::control::FloatControl>(DynamicsControlIds::GAIN + idOffset, "Gain", getGainLaw(), 1.0f, 0);
}

shared_ptr<ctoot::control::FloatControl> DynamicsControls::createInputGainControl()
{
	return make_shared<ctoot::control::FloatControl>(DynamicsControlIds::INPUT_GAIN + idOffset, "Input Gain", INPUT_GAIN_LAW(), 1.0f, 0);
}

shared_ptr<ctoot::control::FloatControl> DynamicsControls::createOutputGainControl()
{
	return make_shared<ctoot::control::FloatControl>(DynamicsControlIds::OUTPUT_GAIN + idOffset, "Output Gain", OUTPUT_GAIN_LAW(), 1.0f, 0);
}

shared_ptr<ctoot::control::BooleanControl> DynamicsControls::createMuteControl()
{
	return make_shared<ctoot::control::BooleanControl>(DynamicsControlIds::MUTE + idOffset, "Mute", false);
}

bool DynamicsControls::hasDepth()
{
    return false;
}

weak_ptr<ControlLaw> DynamicsControls::getDepthLaw()
{
    return DEPTH_LAW();
}

shared_ptr<ctoot::control::FloatControl> DynamicsControls::createDepthControl()
{
    return make_shared<ctoot::control::FloatControl>(DynamicsControlIds::DEPTH + idOffset, "Depth", getDepthLaw(), 1.0f, -40);
}

bool DynamicsControls::hasHysteresis()
{
    return false;
}

weak_ptr<ControlLaw> DynamicsControls::getHysteresisLaw()
{
    return HYSTERESIS_LAW();
}

shared_ptr<ctoot::control::FloatControl> DynamicsControls::createHysteresisControl()
{
    auto hystC = make_shared<ctoot::control::FloatControl>(DynamicsControlIds::HYSTERESIS + idOffset, "Hysteresis", getHysteresisLaw(), 1.0f, 0.0f);
    return hystC;
}

bool DynamicsControls::hasKey()
{
    return false;
}

shared_ptr<ctoot::audio::core::TapControl> DynamicsControls::createKeyControl()
{
	return make_shared<ctoot::audio::core::TapControl>(DynamicsControlIds::KEY + idOffset, "Key");
}

bool DynamicsControls::hasChannelMode() {
	return false;
}

shared_ptr<ctoot::control::EnumControl> DynamicsControls::createDetectionChannelControl() {
	return make_shared<ctoot::audio::dynamics::izcompressor::ChannelControl>(DynamicsControlIds::DETECTION_CHANNEL_MODE + idOffset, "Detection Channel Control");
}

shared_ptr<ctoot::control::EnumControl> DynamicsControls::createAttenuationChannelControl() {
	return make_shared<ctoot::audio::dynamics::izcompressor::ChannelControl>(DynamicsControlIds::ATTENUATION_CHANNEL_MODE + idOffset, "Attenuation Channel Control");
}

float DynamicsControls::getThreshold()
{
    return threshold;
}

float DynamicsControls::getInverseThreshold()
{
    return inverseThreshold;
}

float DynamicsControls::getThresholddB()
{
    return thresholddB;
}

float DynamicsControls::getKneedB()
{
    return kneedB;
}

float DynamicsControls::getInverseRatio()
{
    return inverseRatio;
}

float DynamicsControls::getAttack()
{
    return attack;
}

float DynamicsControls::getLookAhead()
{
	return lookAhead;
}

int32_t DynamicsControls::getHold()
{
    return hold;
}

float DynamicsControls::getRelease()
{
    return release;
}

float DynamicsControls::getDryGain()
{
    return dryGain;
}

float DynamicsControls::getWetGain()
{
	return wetGain;
}

float DynamicsControls::getGain()
{
    return gain;
}

float DynamicsControls::getDepth()
{
    return depth;
}

float DynamicsControls::getHysteresis()
{
    return hysteresis;
}

string DynamicsControls::getDetectionChannelMode() {
	return detectionChannelMode;
}

string DynamicsControls::getAttenuationChannelMode() {
	return attenuationChannelMode;
}

float DynamicsControls::getInputGain() {
	return inputGain;
}

float DynamicsControls::getOutputGain() {
	return outputGain;
}

bool DynamicsControls::getMute() {
	return mute;
}

ctoot::audio::core::AudioBuffer* DynamicsControls::getKeyBuffer()
{
    return key;
}

bool DynamicsControls::isRMS()
{
    return rms;
}

void DynamicsControls::setDynamicGain(float dynamicGain)
{
	if (!gainReductionIndicator.lock())
		return;

	gainReductionIndicator.lock()->setValue(static_cast<float>((int32_t(20) * log(dynamicGain))));
}

weak_ptr<ControlLaw> DynamicsControls::getInverseRatioLaw()
{
    return INVERSE_RATIO_LAW();
}

vector<string> DynamicsControls::ratioPresets2 { "2", "4", "10", "Infinity", "-10", "-4", "-2" };

bool DynamicsControls::isBypassed()
{
    return AudioControls::isBypassed();
}

void DynamicsControls::init() {
	if (initialized) {
		//MLOG("Error: DynamicsControls is already initialized!");
		//MLOG("I'll try to clear and re-init...");
		controls.clear();
	}
	if (hasMute()) {
		auto mc = createMuteControl();
		muteControl = mc;
		derive(mc.get());
		add(std::move(mc));
	}
	if (hasInputGain()) {
		auto igc = createInputGainControl();
		inputGainControl = igc;
		derive(igc.get());
		add(std::move(igc));
	}
	if (hasOutputGain()) {
		auto ogc = createOutputGainControl();
		outputGainControl = ogc;
		derive(ogc.get());
		add(std::move(ogc));
	}
	if (hasLookAhead()) {
		auto lac = createLookAheadControl();
		lookAheadControl = lac;
		derive(lac.get());
		add(std::move(lac));
	}
	if (hasChannelMode()) {
		auto dcc = createDetectionChannelControl();
		detectionChannelControl = dcc;
		derive(dcc.get());
		add(std::move(dcc));
		auto acc = createAttenuationChannelControl();
		attenuationChannelControl = acc;
		derive(acc.get());
		add(std::move(acc));
	}
	if (hasGainReductionIndicator()) {
		auto gri = make_shared<GainReductionIndicator>();
		gainReductionIndicator = gri;
		add(std::move(gri));
	}
	auto g1 = make_shared<ctoot::control::ControlColumn>();
	if (hasKey()) {
		auto kc = createKeyControl();
		keyControl = kc;
		derive(kc.get());
		g1->add(std::move(kc));
	}
	if (hasDepth()) {
		auto dc = createDepthControl();
		depthControl = dc;
		derive(dc.get());
		g1->add(std::move(dc));
	}
	if (hasHysteresis()) {
		auto hc = createHysteresisControl();
		hysteresisControl = hc;
		derive(hc.get());
		g1->add(std::move(hc));
	}
	if (hasKnee()) {
		auto kc = createKneeControl();
		kneeControl = kc;
		derive(kc.get());
		g1->add(std::move(kc));
	}
	if (hasRatio()) {
		auto rc = createRatioControl();
		ratioControl = rc;
		derive(rc.get());
		g1->add(std::move(rc));
	}
	else if (hasInverseRatio()) {
		auto irc = make_shared<InverseRatioControl>(this);
		ratioControl = irc;
		derive(irc.get());
		g1->add(std::move(irc));
	}
	auto tc = createThresholdControl();
	thresholdControl = tc;
	derive(tc.get());
	g1->add(std::move(tc));
	add(std::move(g1));
	auto g2 = make_shared<ctoot::control::ControlColumn>();
	if (hasRMS()) {
		auto rc = createRMSControl();
		rmsControl = rc;
		derive(rc.get());
		g2->add(std::move(rc));
	}
	auto ac = createAttackControl();
	attackControl = ac;
	derive(ac.get());
	g2->add(std::move(ac));
	if (hasHold()) {
		auto hc = createHoldControl();
		holdControl = hc;
		g2->add(std::move(hc));
		derive(hc.get());
	}
	auto rc = createReleaseControl();
	releaseControl = rc;
	derive(rc.get());
	g2->add(std::move(rc));
	add(std::move(g2));

	auto g3 = make_shared<ctoot::control::ControlColumn>();
	auto useg3 = false;
	if (hasWetGain()) {
		auto wgc = createWetGainControl();
		wetGainControl = wgc;
		derive(wgc.get());
		g3->add(std::move(wgc));
		useg3 = true;
	}
	if (hasDryGain()) {
		auto dgc = createDryGainControl();
		dryGainControl = dgc;
		derive(dgc.get());
		g3->add(std::move(dgc));
		useg3 = true;
	}
	if (hasGain()) {
		auto gc = createGainControl();
		gainControl = gc;
		derive(gc.get());
		g3->add(std::move(gc));
		useg3 = true;
	}
	if (useg3) {
		add(std::move(g3));
	}
	initialized = true;
}
