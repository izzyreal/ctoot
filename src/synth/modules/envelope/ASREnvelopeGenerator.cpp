#include <synth/modules/envelope/ASREnvelopeGenerator.hpp>

#include <synth/modules/envelope/ASREnvelopeVariables.hpp>

using namespace ctoot::synth::modules::envelope;

ASREnvelopeGenerator::ASREnvelopeGenerator(ASREnvelopeVariables* vars)
{
    attackCoeff = vars->getAttackCoeff();
    sustain = true;
    releaseCoeff = vars->getReleaseCoeff();
}

float ctoot::synth::modules::envelope::ASREnvelopeGenerator::getEnvelope(bool release)
{
	if (release && state != COMPLETE) state = RELEASE;
	switch (state) {
	case ATTACK:
		envelope += attackCoeff * (1.0f - envelope);
		if (envelope > 0.99f) {
			state = sustain ? SUSTAIN : RELEASE;
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

bool ctoot::synth::modules::envelope::ASREnvelopeGenerator::isComplete()
{
    return state == COMPLETE;
}
