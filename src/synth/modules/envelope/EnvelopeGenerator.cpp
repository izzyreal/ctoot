#include <synth/modules/envelope/EnvelopeGenerator.hpp>

#include <synth/modules/envelope/EnvelopeVariables.hpp>

using namespace ctoot::synth::modules::envelope;

EnvelopeGenerator::EnvelopeGenerator(EnvelopeVariables* vars)
{
    this->vars = vars;
}

float EnvelopeGenerator::getEnvelope(bool release)
{
	if (release && state != COMPLETE) state = RELEASE; // !!!
	switch (state) {
	case DELAY:
		if (--delayCount >= 0) break;
		state = ATTACK;
		// intentional fall through
	case ATTACK:
		envelope += attackCoeff; // * (1f - envelope);
		if (envelope > 0.99f) {
			state = HOLD;
		}
		break;
	case HOLD:
		if (--holdCount >= 0) break;
		state = DECAY;
		// intentional fall through
	case DECAY:
		envelope -= decayCoeff * envelope;
		if (envelope <= sustainLevel + 0.001f) {
			state = SUSTAIN;
		}
		break;
	case SUSTAIN:
		break;
	case RELEASE:
		envelope -= releaseCoeff * envelope;
		if (envelope < 0.001f) { // -60dB cutoff !!!
			envelope = 0.0f;
			state = COMPLETE;
		}
		break;
	case COMPLETE:
		break;
	}
	return envelope;
}

bool ctoot::synth::modules::envelope::EnvelopeGenerator::isComplete()
{
    return state == COMPLETE;
}

void EnvelopeGenerator::trigger()
{
    delayCount = vars->getDelayCount();
    attackCoeff = vars->getAttackCoeff();
    holdCount = vars->getHoldCount();
    decayCoeff = vars->getDecayCoeff();
    sustainLevel = vars->getSustainLevel();
    releaseCoeff = vars->getReleaseCoeff();
    state = DELAY;
}
