#include "SysexMessage.hpp"

#include <VecUtil.hpp>

using namespace ctoot::midi::core;
using namespace std;

SysexMessage::SysexMessage()
{
}


const vector<char> SysexMessage::getData()
{
	vector<char> returnedArray(length - 1);
	moduru::VecUtil::VecCopy(data, 1, returnedArray, 0, (length - 1));
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