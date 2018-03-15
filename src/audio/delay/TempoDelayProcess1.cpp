#include <audio/delay/TempoDelayProcess1.hpp>

#include <audio/delay/TempoDelayProcess.hpp>

using namespace ctoot::audio::delay;

TempoDelayProcess1::TempoDelayProcess1(TempoDelayProcess *TempoDelayProcess_this)
    : TempoDelayProcess_this(TempoDelayProcess_this)
{
}

/*
void TempoDelayProcess1::tempoChanged(float newTempo)
{
    TempoDelayProcess_this->bpm = newTempo;
}
*/