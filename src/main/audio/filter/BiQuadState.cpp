#include <audio/filter/BiQuadState.hpp>

using namespace ctoot::audio::filter; 

BiQuadState::BiQuadState()
{
    clear();
}

void BiQuadState::clear()
{
    x1 = 0;
    x2 = 0;
    y1 = 0;
    y2 = 0;
}
