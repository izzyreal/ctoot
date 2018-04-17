#include <audio/dynamics/izcompressor/IzBandCompressorControls.hpp>

#include <audio/dynamics/CompressorControls.hpp>
#include <audio/dynamics/DynamicsControlIds.hpp>
#include <audio/dynamics/DynamicsIds.hpp>
#include <audio/dynamics/izcompressor/IzCompressorControls.hpp>
#include <control/Control.hpp>

using namespace ctoot::audio::dynamics;
using namespace ctoot::audio::dynamics::izcompressor;
using namespace std;

IzBandCompressorControls::IzBandCompressorControls(string band)
	: ctoot::audio::core::AudioControls(DynamicsIds::MID_SIDE_COMPRESSOR_ID, "IzBand Compressor")
{
	auto cc = make_shared<IzCompressorControls>(band, 0);
	compressorControls = cc;
	add(std::move(cc));
	deriveIndependentVariables();
	deriveDependentVariables();
}

IzBandCompressorControls::IzBandCompressorControls()
	: ctoot::audio::core::AudioControls(DynamicsIds::MID_SIDE_COMPRESSOR_ID, "IzBand Compressor")
{
	auto cc = make_shared<IzCompressorControls>("Band", 0);
	compressorControls = cc;
	add(std::move(cc));
    deriveIndependentVariables();
    deriveDependentVariables();
}

void IzBandCompressorControls::deriveIndependentVariables()
{
    threshold = compressorControls.lock()->getThreshold();
    inverseThreshold = compressorControls.lock()->getInverseThreshold();
    inverseRatio = compressorControls.lock()->getInverseRatio();
    gain = compressorControls.lock()->getGain();
    depth = compressorControls.lock()->getDepth();
	detectionChannelMode = compressorControls.lock()->getDetectionChannelMode();
	attenuationChannelMode = compressorControls.lock()->getAttenuationChannelMode();
	inputGain = compressorControls.lock()->getInputGain();
}

void IzBandCompressorControls::deriveDependentVariables()
{
    attack = compressorControls.lock()->getAttack();
    release = compressorControls.lock()->getRelease();
	lookAhead = compressorControls.lock()->getLookAhead();
}

void IzBandCompressorControls::derive(ctoot::control::Control* c)
{
	auto id = c->getId();
	auto n = 0;
	auto cc = compressorControls;
	switch (id) {
	case DynamicsControlIds::THRESHOLD:
		threshold = cc.lock()->getThreshold();
		inverseThreshold = cc.lock()->getInverseThreshold();
	case DynamicsControlIds::RATIO:
		inverseRatio = cc.lock()->getInverseRatio();
		break;
	case DynamicsControlIds::ATTACK:
		attack = cc.lock()->getAttack();
		break;
	case DynamicsControlIds::HOLD:
		hold = cc.lock()->getHold();
		break;
	case DynamicsControlIds::RELEASE:
		release = cc.lock()->getRelease();
		break;
	case DynamicsControlIds::GAIN:
		gain = cc.lock()->getGain();
		break;
	case DynamicsControlIds::DEPTH:
		depth = cc.lock()->getDepth();
		break;
	case DynamicsControlIds::DETECTION_CHANNEL_MODE:
		detectionChannelMode = cc.lock()->getDetectionChannelMode();
		break;
	case DynamicsControlIds::ATTENUATION_CHANNEL_MODE:
		attenuationChannelMode = cc.lock()->getAttenuationChannelMode();
		break;
	case DynamicsControlIds::INPUT_GAIN:
		inputGain = cc.lock()->getInputGain();
		break;
	case DynamicsControlIds::LOOK_AHEAD:
		lookAhead = cc.lock()->getLookAhead();
		break;
	}
}

void IzBandCompressorControls::update(float sampleRate)
{
    compressorControls.lock()->update(sampleRate);
    deriveDependentVariables();
}

float IzBandCompressorControls::getLookAhead()
{
	return lookAhead;
}

float IzBandCompressorControls::getThreshold()
{
    return threshold;
}

float IzBandCompressorControls::getInverseThreshold()
{
    return inverseThreshold;
}

float IzBandCompressorControls::getKnee()
{
    return knee;
}

float IzBandCompressorControls::getInverseRatio()
{
    return inverseRatio;
}

float IzBandCompressorControls::getAttack()
{
    return attack;
}

float IzBandCompressorControls::getRelease()
{
    return release;
}

float IzBandCompressorControls::getGain()
{
    return gain;
}

float IzBandCompressorControls::getDepth()
{
    return depth;
}

void IzBandCompressorControls::setDynamicGain(float gain)
{
    compressorControls.lock()->setDynamicGain(gain);
}

bool IzBandCompressorControls::isBypassed()
{
    return AudioControls::isBypassed();
}

string IzBandCompressorControls::getDetectionChannelMode() {
	return detectionChannelMode;
}

string IzBandCompressorControls::getAttenuationChannelMode() {
	return attenuationChannelMode;
}

float IzBandCompressorControls::getInputGain() {
	return inputGain;
}
