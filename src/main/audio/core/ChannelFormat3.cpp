#include <audio/core/ChannelFormat3.hpp>

using namespace std;
using namespace ctoot::audio::core;

ChannelFormat3::ChannelFormat3()
{
}

int ChannelFormat3::getCount()
{
    return 4;
}

int ChannelFormat3::getCenter()
{
    return -1;
}

int ChannelFormat3::getLFE()
{
    return -1;
}

std::vector<int8_t> ChannelFormat3::getLeft()
{
    return left;
}

std::vector<int8_t> ChannelFormat3::getRight()
{
    return right;
}

string ChannelFormat3::getName()
{
    return "Quad";
}

string ChannelFormat3::getName(int chan)
{
	switch (chan) {
	case 0:
		return "Front.Left";
	case 1:
		return "Front.Right";
	case 2:
		return "Rear.Left";
	case 3:
		return "Rear Right";
	default:
		return "illegal channel";
	}
}