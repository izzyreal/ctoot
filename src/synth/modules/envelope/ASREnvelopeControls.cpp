#include <synth/modules/envelope/ASREnvelopeControls.hpp>

#include <control/BooleanControl.hpp>
#include <control/Control.hpp>
#include <control/FloatControl.hpp>
#include <control/LogLaw.hpp>
#include <synth/modules/envelope/EnvelopeControlIds.hpp>
#include <synth/modules/envelope/EnvelopeIds.hpp>

#include <cmath>

using namespace ctoot::synth::modules::envelope;
using namespace std;

ASREnvelopeControls::ASREnvelopeControls(int32_t instanceIndex, std::string name, int32_t idOffset)
	: ASREnvelopeControls(instanceIndex, name, idOffset, 1.0f)
{
}

ASREnvelopeControls::ASREnvelopeControls(int32_t instanceIndex, std::string name, int32_t idOffset, float timeMultiplier)
	: ASREnvelopeControls(EnvelopeIds::DAHDSR_ENVELOPE_ID, instanceIndex, name, idOffset, timeMultiplier)
{
}

ASREnvelopeControls::ASREnvelopeControls(int32_t id, int32_t instanceIndex, std::string name, int32_t idOffset, float timeMultiplier)
	: ctoot::control::CompoundControl(id, instanceIndex, name)
{
    this->idOffset = idOffset;
    this->timeMultiplier = timeMultiplier;
    createControls();
    deriveSampleRateIndependentVariables();
    deriveSampleRateDependentVariables();
}

void ASREnvelopeControls::derive(ctoot::control::Control* c)
{
	switch (c->getId() - idOffset) {
	case EnvelopeControlIds::ATTACK:
		attack = deriveAttack();
		break;
	case EnvelopeControlIds::SUSTAIN:
		sustain = deriveSustain();
		break;
	case EnvelopeControlIds::RELEASE:
		release = deriveRelease();
		break;
	}
}

bool ASREnvelopeControls::hasDelay()
{
    return true;
}

void ASREnvelopeControls::createControls()
{
	auto m = timeMultiplier;

	auto ac = createAttackControl(1.0f, 10000.0f * m, 1.0f);
	attackControl = ac;
	add(std::move(ac));

	auto sc = createSustainControl();
	sustainControl = sc;
	add(std::move(sc));

	auto rc = createReleaseControl(20, 2000 * m, 200.0f);
	releaseControl = rc;
	add(std::move(rc));
}

void ASREnvelopeControls::deriveSampleRateIndependentVariables()
{
    sustain = deriveSustain();
}

void ASREnvelopeControls::deriveSampleRateDependentVariables()
{
    attack = deriveAttack();
    release = deriveRelease();
}

bool ASREnvelopeControls::deriveSustain()
{
    return sustainControl.lock()->getValue();
}

float ASREnvelopeControls::LOG_0_01 = log(0.01);

float ASREnvelopeControls::deriveTimeFactor(float milliseconds)
{
    auto ns = milliseconds * sampleRate / int32_t(1000);
    auto k = LOG_0_01 / ns;
    return static_cast< float >((1.0f - exp(k)));
}

float ASREnvelopeControls::deriveAttack()
{
    return deriveTimeFactor(attackControl.lock()->getValue());
}

float ASREnvelopeControls::deriveRelease()
{
    return deriveTimeFactor(releaseControl.lock()->getValue());
}

shared_ptr<ctoot::control::FloatControl> ASREnvelopeControls::createAttackControl(float min, float max, float init_)
{
    static auto law = make_shared<ctoot::control::LogLaw>(min, max, "ms");
    return make_shared<ctoot::control::FloatControl>(EnvelopeControlIds::ATTACK + idOffset, "Attack", law, 0.1f, init_);
}

shared_ptr<ctoot::control::BooleanControl> ASREnvelopeControls::createSustainControl()
{
    return make_shared<ctoot::control::BooleanControl>(EnvelopeControlIds::SUSTAIN + idOffset, "Sustain", true, "on", "off");
}

shared_ptr<ctoot::control::FloatControl> ASREnvelopeControls::createReleaseControl(float min, float max, float init_)
{
	static auto law = make_shared<ctoot::control::LogLaw>(min, max, "ms");
	return make_shared<ctoot::control::FloatControl>(EnvelopeControlIds::RELEASE + idOffset, "Release", law, 1.0f, init_);
}

float ASREnvelopeControls::getAttackCoeff()
{
    return attack;
}

bool ASREnvelopeControls::getSustain()
{
    return sustain;
}

float ASREnvelopeControls::getReleaseCoeff()
{
    return release;
}

void ASREnvelopeControls::setSampleRate(int32_t rate)
{
	if (sampleRate != rate) {
		sampleRate = rate;
		deriveSampleRateDependentVariables();
	}
}
