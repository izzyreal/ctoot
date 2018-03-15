#include <audio/core/ChannelFormat1.hpp>

using namespace ctoot::audio::core;
using namespace std;

ChannelFormat1::ChannelFormat1()
{
}


int ChannelFormat1::getCount()
{
    return 1;
}

bool ChannelFormat1::isCenter(int chan)
{
    return true;
}

bool ChannelFormat1::isLeft(int chan)
{
    return false;
}

bool ChannelFormat1::isRight(int chan)
{
    return false;
}

bool ChannelFormat1::isFront(int chan)
{
    return true;
}

bool ChannelFormat1::isRear(int chan)
{
    return false;
}

bool ChannelFormat1::isLFE(int chan)
{
    return false;
}

int ChannelFormat1::getCenter()
{
    return 0;
}

int ChannelFormat1::getLFE()
{
    return -1;
}

int8_t* ChannelFormat1::getLeft()
{
    return empty;
}

int8_t* ChannelFormat1::getRight()
{
    return empty;
}

string ChannelFormat1::getName()
{
	return "Mono";
}

string ChannelFormat1::getName(int chan)
{
	return "Centre";
}
