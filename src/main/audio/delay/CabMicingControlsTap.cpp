#include <audio/delay/CabMicingControlsTap.hpp>

using namespace ctoot::audio::delay;
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
