#include <audio/core/ChannelFormat4.hpp>

using namespace std;
using namespace ctoot::audio::core;

ChannelFormat4::ChannelFormat4()
{
}

int ChannelFormat4::getCount()
{
    return 6;
}

int ChannelFormat4::getCenter()
{
    return 4;
}

int ChannelFormat4::getLFE()
{
    return 5;
}

std::vector<int8_t> ChannelFormat4::getLeft()
{
    return left;
}

std::vector<int8_t> ChannelFormat4::getRight()
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