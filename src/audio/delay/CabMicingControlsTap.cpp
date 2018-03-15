#include <audio/delay/CabMicingControlsTap.hpp>

#include <audio/delay/CabMicingControls.hpp>

using namespace ctoot::audio::delay;
using namespace ctoot::control;
using namespace std;

CabMicingControlsTap::CabMicingControlsTap() {
}

float ctoot::audio::delay::CabMicingControlsTap::getDelayMilliseconds()
{
    return millis;
}

float ctoot::audio::delay::CabMicingControlsTap::getLevel()
{
    return level;
}
