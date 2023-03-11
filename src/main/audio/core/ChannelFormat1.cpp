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

int ChannelFormat1::getCenter()
{
    return 0;
}

int ChannelFormat1::getLFE()
{
    return -1;
}

std::vector<int8_t> ChannelFormat1::getLeft()
{
    return empty;
}

std::vector<int8_t> ChannelFormat1::getRight()
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
