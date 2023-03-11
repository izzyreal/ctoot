#include <synth/modules/envelope/EnvelopeControls.hpp>

#include <control/Control.hpp>
#include <control/FloatControl.hpp>
#include <control/LinearLaw.hpp>
#include <control/LogLaw.hpp>
#include <synth/modules/envelope/EnvelopeControlIds.hpp>
#include <synth/modules/envelope/EnvelopeIds.hpp>

#include <cmath>

using namespace ctoot::synth::modules::envelope;
using namespace std;

std::vector<std::shared_ptr<ctoot::control::ControlLaw>> EnvelopeControls::laws;

EnvelopeControls::EnvelopeControls(int32_t instanceIndex, std::string name, int32_t idOffset, std::string options, float timeMultiplier)
	: EnvelopeControls(EnvelopeIds::DAHDSR_ENVELOPE_ID, instanceIndex, name, idOffset, options, timeMultiplier)
{
}

EnvelopeControls::EnvelopeControls(int32_t id, int32_t instanceIndex, std::string name, int32_t idOffset, std::string options, float timeMultiplier)
	: ctoot::control::CompoundControl(id, instanceIndex, name)
{
	this->idOffset = idOffset;
	hasDelay = options[0] == 'D';
	hasHold = options.find("H") != string::npos;
	hasSustain = options.find("S") != string::npos;
	this->timeMultiplier = timeMultiplier;
	createControls();
	deriveSampleRateIndependentVariables();
	deriveSampleRateDependentVariables();
}

void EnvelopeControls::derive(ctoot::control::Control* c)
{
	switch (c->getId() - idOffset) {
	case EnvelopeControlIds::DELAY:
		delay = deriveDelay();
		break;
	case EnvelopeControlIds::ATTACK:
		attack = deriveAttack();
		break;
	case EnvelopeControlIds::HOLD:
		hold = deriveHold();
		break;
	case EnvelopeControlIds::DECAY:
		decay = deriveDecay();
		break;
	case EnvelopeControlIds::SUSTAIN:
		sustain = deriveSustain();
		break;
	case EnvelopeControlIds::RELEASE:
		release = deriveRelease();
		break;
	}
}

void EnvelopeControls::createControls()
{
	auto m = timeMultiplier;
	if (hasDelay) {
		auto dc = createDelayControl(0.0f, 1000.0f * m, 0.0f);
		delayControl = dc;
		add(std::move(dc));
	}

	auto ac = createAttackControl(1.0f, 10000.0f * m, 1.0f);
	attackControl = ac;
	add(std::move(ac));

	if (hasHold) {
		auto hc = createHoldControl(0, 1000, 10);
		holdControl = hc;
		add(std::move(hc));
	}
	if (hasSustain) {
		auto dc = createDecayControl(20.0f, 20000.0f * m, 200.0f);
		decayControl = dc;
		add(std::move(dc));

		auto sc = createSustainControl();
		sustainControl = sc;
		add(std::move(sc));
	}
	auto rc = createReleaseControl(20, int32_t(2000) * m, 200.0f);
	releaseControl = rc;
	add(std::move(rc));
}

void EnvelopeControls::deriveSampleRateIndependentVariables()
{
    sustain = deriveSustain();
}

void EnvelopeControls::deriveSampleRateDependentVariables()
{
    delay = deriveDelay();
    attack = deriveAttack();
    hold = deriveHold();
    decay = deriveDecay();
    release = deriveRelease();
}

float EnvelopeControls::LOG_0_01 = log(0.01);

float EnvelopeControls::deriveTimeFactor(float milliseconds)
{
    auto ns = milliseconds * sampleRate / int32_t(1000);
    auto k = LOG_0_01 / ns;
    return static_cast< float >(1.0f - exp(k));
}

int32_t EnvelopeControls::deriveDelay()
{
    if(!hasDelay)
        return 0;

    return static_cast< int32_t >((delayControl.lock()->getValue() * sampleRate / int32_t(1000)));
}

float EnvelopeControls::deriveAttack()
{
    auto ns = attackControl.lock()->getValue() * sampleRate / int32_t(1000);
    return int32_t(1) / ns;
}

int32_t EnvelopeControls::deriveHold()
{
	if (!hasHold)
		return 0;

	return static_cast<int32_t>((holdControl.lock()->getValue() * sampleRate / int32_t(1000)));
}

float EnvelopeControls::deriveDecay()
{
	if (!hasSustain)
		return 0.001f;

	return deriveTimeFactor(decayControl.lock()->getValue());
}

float EnvelopeControls::deriveSustain()
{
	if (!hasSustain)
		return 1.0f;

	return sustainControl.lock()->getValue();
}

float EnvelopeControls::deriveRelease()
{
	return deriveTimeFactor(releaseControl.lock()->getValue());
}

shared_ptr<ctoot::control::FloatControl> EnvelopeControls::createDelayControl(float min, float max, float init_)
{
	auto law = make_shared<ctoot::control::LinearLaw>(min, max, "ms");
	auto res = make_shared<ctoot::control::FloatControl>(EnvelopeControlIds::DELAY + idOffset, "Delay", law, 1.0f, init_);
	laws.push_back(std::move(law));
	return res;
}

shared_ptr<ctoot::control::FloatControl> EnvelopeControls::createAttackControl(float min, float max, float init_)
{
	auto law = make_shared<ctoot::control::LogLaw>(min, max, "ms");
	auto res = make_shared<ctoot::control::FloatControl>(EnvelopeControlIds::ATTACK + idOffset, "Attack", law, 0.1f, init_);
	laws.push_back(std::move(law));
    return res;
}

shared_ptr<ctoot::control::FloatControl> EnvelopeControls::createHoldControl(float min, float max, float init_)
{
    auto law = make_shared<ctoot::control::LinearLaw>(min, max, "ms");
	auto res = make_shared<ctoot::control::FloatControl>(EnvelopeControlIds::HOLD + idOffset, "Hold", law, 1.0f, init_);
	laws.push_back(std::move(law));
    return res;
}

shared_ptr<ctoot::control::FloatControl> EnvelopeControls::createDecayControl(float min, float max, float init_)
{
    auto law = make_shared<ctoot::control::LogLaw>(min, max, "ms");
	auto res = make_shared<ctoot::control::FloatControl>(EnvelopeControlIds::DECAY + idOffset, "Decay", law, 1.0f, init_);
	laws.push_back(std::move(law));
    return res;
}

shared_ptr<ctoot::control::FloatControl> EnvelopeControls::createSustainControl()
{
    return make_shared<ctoot::control::FloatControl>(EnvelopeControlIds::SUSTAIN + idOffset, "Sustain", ctoot::control::LinearLaw::UNITY(), 0.01f, 0.5f);
}

shared_ptr<ctoot::control::FloatControl> EnvelopeControls::createReleaseControl(float min, float max, float init_)
{
    auto law = make_shared<ctoot::control::LogLaw>(min, max, "ms");
	auto res = make_shared<ctoot::control::FloatControl>(EnvelopeControlIds::RELEASE + idOffset, "Release", law, 1.0f, init_);
	laws.push_back(std::move(law));
    return res;
}

int32_t EnvelopeControls::getDelayCount()
{
    return delay;
}

float EnvelopeControls::getAttackCoeff()
{
    return attack;
}

int32_t EnvelopeControls::getHoldCount()
{
    return hold;
}

float EnvelopeControls::getDecayCoeff()
{
    return decay;
}

float EnvelopeControls::getSustainLevel()
{
    return sustain;
}

float EnvelopeControls::getReleaseCoeff()
{
    return release;
}

void EnvelopeControls::setSampleRate(int32_t rate)
{
	if (sampleRate != rate) {
		sampleRate = rate;
		deriveSampleRateDependentVariables();
	}
}
