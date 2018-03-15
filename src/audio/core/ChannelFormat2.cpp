#include <audio/core/ChannelFormat2.hpp>

using namespace ctoot::audio::core;
using namespace std;

ChannelFormat2::ChannelFormat2()
{
	left[0] = 0;
	right[0] = 1;
}

int ChannelFormat2::getCount()
{
    return 2;
}

bool ChannelFormat2::isCenter(int chan)
{
    return false;
}

bool ChannelFormat2::isLeft(int chan)
{
    return chan == 0;
}

bool ChannelFormat2::isRight(int chan)
{
    return chan == 1;
}

bool ChannelFormat2::isFront(int chan)
{
    return true;
}

bool ChannelFormat2::isRear(int chan)
{
    return false;
}

bool ChannelFormat2::isLFE(int chan)
{
    return false;
}

int ChannelFormat2::getCenter()
{
    return -1;
}

int ChannelFormat2::getLFE()
{
    return -1;
}

int8_t* ChannelFormat2::getLeft()
{
    return left;
}

int8_t* ChannelFormat2::getRight()
{
    return right;
}

string ChannelFormat2::getName()
{
	return "Stereo";
}

string ChannelFormat2::getName(int chan)
{
    switch (chan) {
    case 0:
        return "Left";
    case 1:
        return "Right";
    default:
		return "illegal channel";
    }

}