#include <synth/modules/envelope/EnvelopeGenerator.hpp>

#include <synth/modules/envelope/EnvelopeVariables.hpp>

using namespace ctoot::synth::modules::envelope;

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
