#include "SysexMessage.hpp"

#include <VecUtil.hpp>

using namespace ctoot::midi::core;
using namespace std;

SysexMessage::SysexMessage()
{
}

SysexMessage::SysexMessage(const vector<char>& data)
	: MidiMessage(data)
{
}

SysexMessage::SysexMessage(const vector<char>& data, int32_t length)
	: MidiMessage(data)
{
}

constexpr int32_t SysexMessage::SPECIAL_SYSTEM_EXCLUSIVE;
constexpr int32_t SysexMessage::SYSTEM_EXCLUSIVE;


const vector<char> SysexMessage::getData()
{
	vector<char> returnedArray(length - 1);
	moduru::VecUtil::VecCopy(&data, 1, &returnedArray, 0, (length - 1));
	return returnedArray;
}

/*
void javax::sound::midi::SysexMessage::setMessage(::int8_tArray* data, int32_t length)
{ 
}

void javax::sound::midi::SysexMessage::setMessage(int32_t status, ::int8_tArray* data, int32_t length)
{
}
*/