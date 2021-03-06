#include "SysexMsg.hpp"

#include <midi/core/SysexMessage.hpp>

using namespace ctoot::midi::message;
using namespace ctoot::midi::core;
using namespace std;

SysexMsg::SysexMsg()
{
}

bool SysexMsg::isSysex(MidiMessage* msg)
{
    return isSysex(getStatus(msg));
}

bool SysexMsg::isSysex(int32_t status)
{
    return status == END_OF_EXCLUSIVE || status == SPECIAL_SYSTEM_EXCLUSIVE || status == SYSTEM_EXCLUSIVE;
}

MidiMessage* SysexMsg::createSysex(const vector<char>& data, int32_t length)
{
    auto sysex = new SysexMessage();
    sysex->setMessage(data, length);
    return sysex;
}

const unsigned char SysexMsg::SYSTEM_EXCLUSIVE;
const unsigned char SysexMsg::SPECIAL_SYSTEM_EXCLUSIVE;
const unsigned char SysexMsg::END_OF_EXCLUSIVE;
const unsigned char SysexMsg::ID_NON_COMMERCIAL;
