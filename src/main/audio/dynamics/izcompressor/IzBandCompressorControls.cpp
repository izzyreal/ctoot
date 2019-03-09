#include "IzBandCompressorControls.hpp"

#include <audio/dynamics/CompressorControls.hpp>
#include <audio/dynamics/DynamicsControlIds.hpp>
#include <audio/dynamics/DynamicsIds.hpp>
#include <audio/dynamics/izcompressor/IzCompressorControls.hpp>
#include <control/Control.hpp>

using namespace ctoot::audio::dynamics;
using namespace ctoot::audio::dynamics::izcompressor;
using namespace std;

IzBandCompressorControls::IzBandCompressorControls(string band, int idOffset)
	: ctoot::audio::core::AudioControls(DynamicsIds::MID_SIDE_COMPRESSOR_ID, "IzBand Compressor", idOffset + DynamicsControlIds::BYPASS)
{
	auto cc = make_shared<IzCompressorControls>(band, idOffset);
	this->idOffset = idOffset;
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
	auto cl = compressorControls.lock();
	threshold = cl->getThreshold();
    inverseThreshold = cl->getInverseThreshold();
    inverseRatio = cl->getInverseRatio();
    gain = cl->getGain();
    depth = cl->getDepth();
	detectionChannelMode = cl->getDetectionChannelMode();
	attenuationChannelMode = cl->getAttenuationChannelMode();
	inputGain = cl->getInputGain();
	outputGain = cl->getOutputGain();
	mute = cl->getMute();
	solo = cl->getSolo();
	dryGain = cl->getDryGain();
	wetGain = cl->getWetGain();
	keyBuffer = cl->getKeyBuffer();
}

void IzBandCompressorControls::deriveDependentVariables()
{
	auto cl = compressorControls.lock();
    attack = cl->getAttack();
    release = cl->getRelease();
	lookAhead = cl->getLookAhead();
}

void IzBandCompressorControls::derive(ctoot::control::Control* c)
{
	auto id = c->getId() - idOffset;
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
	case DynamicsControlIds::OUTPUT_GAIN:
		outputGain = cc.lock()->getOutputGain();
		break;
	case DynamicsControlIds::LOOK_AHEAD:
		lookAhead = cc.lock()->getLookAhead();
		break;
	case DynamicsControlIds::MUTE:
		mute = cc.lock()->getMute();
		break;
	case DynamicsControlIds::DRY_GAIN:
		dryGain = cc.lock()->getDryGain();
		break;
	case DynamicsControlIds::WET_GAIN:
		wetGain = cc.lock()->getWetGain();
		break;
	case DynamicsControlIds::SOLO:
		solo = cc.lock()->getSolo();
		break;
	case DynamicsControlIds::KEY:
		keyBuffer = cc.lock()->getKeyBuffer();
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

bool IzBandCompressorControls::getMute() {
	return mute;
}

bool IzBandCompressorControls::getSolo() {
	return solo;
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

float IzBandCompressorControls::getOutputGain() {
	return outputGain;
}

float IzBandCompressorControls::getDryGain() {
	return dryGain;
}

float IzBandCompressorControls::getWetGain() {
	return wetGain;
}

ctoot::audio::core::AudioBuffer* IzBandCompressorControls::getKeyBuffer() {
	return keyBuffer;
}

void IzBandCompressorControls::setLink(weak_ptr<IzCompressorProcessVariables> link) {
	this->link = link;
}

weak_ptr<IzCompressorProcessVariables> IzBandCompressorControls::getLink() {
	return link;
}
