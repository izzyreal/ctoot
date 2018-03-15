#include <audio/core/ChannelFormat4.hpp>

using namespace std;
using namespace ctoot::audio::core;

ChannelFormat4::ChannelFormat4()
{
	left[0] = 0;
	left[1] = 2;
	right[0] = 1;
	right[1] = 3;
}

int ChannelFormat4::getCount()
{
    return 6;
}

bool ChannelFormat4::isCenter(int chan)
{
    return chan == getCenter();
}

bool ChannelFormat4::isLeft(int chan)
{
    return chan < 4 && (chan & 1) == 0;
}

bool ChannelFormat4::isRight(int chan)
{
    return chan < 4 && (chan & 1) == 1;
}

bool ChannelFormat4::isFront(int chan)
{
    return chan < 2 || chan == 4;
}

bool ChannelFormat4::isRear(int chan)
{
    return chan >= 2 && chan < 4;
}

bool ChannelFormat4::isLFE(int chan)
{
    return chan == getLFE();
}

int ChannelFormat4::getCenter()
{
    return 4;
}

int ChannelFormat4::getLFE()
{
    return 5;
}

int8_t* ChannelFormat4::getLeft()
{
    return left;
}

int8_t* ChannelFormat4::getRight()
{
    return right;
}

string ChannelFormat4::getName()
{
	return "5.1";
}

string ChannelFormat4::getName(int chan)
{
    switch (chan) {
    case 0:
        return "Front.Left";
    case 1:
        return "Front.Right";
    case 2:
        return "Rear.Left";
    case 3:
        return "Rear.Right";
    case 4:
        return "Centre";
    case 5:
      return "LFE";
    default:
        return "illegal channel";
    }

}