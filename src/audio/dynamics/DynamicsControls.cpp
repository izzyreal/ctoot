#include "DynamicsControls.hpp"

#include <dsp/VolumeUtils.hpp>
#include <audio/core/AudioBuffer.hpp>
#include <audio/core/KVolumeUtils.hpp>
#include <audio/core/TapControl.hpp>
#include <audio/dynamics/DynamicsControlIds.hpp>
#include <audio/dynamics/InverseRatioControl.hpp>
#include <audio/dynamics/GainReductionIndicator.hpp>
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

void ctoot::audio::dynamics::DynamicsControls::init()
{
    sampleRate = 44100.0f;
    kneedB = 10.0f;
    gain = 1.0f;
    dryGain = 0.0f;
    depth = 40.0f;
    hysteresis = 0.0f;
    rms = false;
    hold = 0;
    idOffset = 0;
}

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
	static auto res = make_shared<LinearLaw>(int32_t(1), -int32_t(1), "");
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
	static auto res = make_shared<LinearLaw>(-40.0f, 0.0f, "dB");
	return res;
}

weak_ptr<ctoot::control::ControlLaw> DynamicsControls::GAIN_LAW()
{
	static auto res = make_shared<LinearLaw>(0.0f, 20.0f, "dB");
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
	init();
	this->idOffset = idOffset;
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
}

void DynamicsControls::update(float sampleRate)
{
    this->sampleRate = sampleRate;
    deriveAttack();
    deriveHold();
    deriveRelease();
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
    }

}

void DynamicsControls::deriveThreshold()
{
	thresholddB = thresholdControl.lock()->getValue();
	threshold = static_cast<float>(ctoot::audio::core::KVolumeUtils::log2lin(thresholddB));
	inverseThreshold = 1.0f / threshold;
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

bool DynamicsControls::hasGainReductionIndicator()
{
    return false;
}

ctoot::control::ControlLaw* DynamicsControls::getThresholdLaw()
{
	return THRESH_LAW().lock().get();
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

ctoot::control::ControlLaw* DynamicsControls::getAttackLaw()
{
	return ATTACK_LAW().lock().get();
}

shared_ptr<ctoot::control::FloatControl> DynamicsControls::createAttackControl()
{
    auto law = getAttackLaw();
    return make_shared<ctoot::control::FloatControl>(DynamicsControlIds::ATTACK + idOffset, "Attack", law, 0.1f, law->getMinimum());
}

bool DynamicsControls::hasHold()
{
    return false;
}

ctoot::control::ControlLaw* DynamicsControls::getHoldLaw()
{
	return HOLD_LAW().lock().get();
}

shared_ptr<ctoot::control::FloatControl> DynamicsControls::createHoldControl()
{
    return make_shared<ctoot::control::FloatControl>(DynamicsControlIds::HOLD + idOffset, "Hold", getHoldLaw(), 1.0f, 10.0f);
}

ctoot::control::ControlLaw* DynamicsControls::getReleaseLaw()
{
	return RELEASE_LAW().lock().get();
}

shared_ptr<ctoot::control::FloatControl> DynamicsControls::createReleaseControl()
{
    auto law = getReleaseLaw();
    return make_shared<ctoot::control::FloatControl>(DynamicsControlIds::RELEASE + idOffset, "Release", law, 1.0f, law->getMinimum());
}

bool DynamicsControls::hasDryGain()
{
    return false;
}

ctoot::control::ControlLaw* DynamicsControls::getDryGainLaw()
{
    return DRY_GAIN_LAW().lock().get();
}

shared_ptr<ctoot::control::FloatControl> DynamicsControls::createDryGainControl()
{
    return make_shared<ctoot::control::FloatControl>(DynamicsControlIds::DRY_GAIN + idOffset, "Dry", getDryGainLaw(), 1.0f, int32_t(0));
}

bool DynamicsControls::hasGain()
{
    return false;
}

ctoot::control::ControlLaw* DynamicsControls::getGainLaw()
{
    return GAIN_LAW().lock().get();
}

shared_ptr<ctoot::control::FloatControl> DynamicsControls::createGainControl()
{
    return make_shared<ctoot::control::FloatControl>(DynamicsControlIds::GAIN + idOffset, "Gain", getGainLaw(), 1.0f, int32_t(0));
}

bool DynamicsControls::hasDepth()
{
    return false;
}

ctoot::control::ControlLaw* DynamicsControls::getDepthLaw()
{
    return DEPTH_LAW().lock().get();
}

shared_ptr<ctoot::control::FloatControl> DynamicsControls::createDepthControl()
{
    auto depthC = make_shared<ctoot::control::FloatControl>(DynamicsControlIds::DEPTH + idOffset, "Depth", getDepthLaw(), 1.0f, -int32_t(40));
    return depthC;
}

bool DynamicsControls::hasHysteresis()
{
    return false;
}

ctoot::control::ControlLaw* DynamicsControls::getHysteresisLaw()
{
    return HYSTERESIS_LAW().lock().get();
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

ctoot::control::ControlLaw* DynamicsControls::getInverseRatioLaw()
{
    return INVERSE_RATIO_LAW().lock().get();
}

vector<string> DynamicsControls::ratioPresets2 { "2", "4", "10", "Infinity", "-10", "-4", "-2" };

bool DynamicsControls::isBypassed()
{
    return AudioControls::isBypassed();
}
