#include <midi/core/MidiMessage.hpp>

using namespace ctoot::midi::core;
using namespace std;

MidiMessage::MidiMessage()
{
}

MidiMessage::MidiMessage(const vector<char>& _data)
: data (_data), length (data.size())
{
}

MidiMessage* MidiMessage::clone()
{
	return {};
}

int MidiMessage::getLength()
{
	return static_cast<int>(data.size());
}

vector<char>* MidiMessage::getMessage()
{
	return &data;
}

int MidiMessage::getStatus()
{
	return data[0] & 0xFF;
}

void MidiMessage::setMessage(const vector<char>& data, int length)
{
	this->data = data;
}
