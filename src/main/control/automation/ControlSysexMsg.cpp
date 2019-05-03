#include "ControlSysexMsg.hpp"

//#include <midi/core/InvalidMidiDataException.hpp>
#include <midi/core/MidiMessage.hpp>

using namespace ctoot::control::automation;
using namespace ctoot::midi::core;
using namespace std;

ControlSysexMsg::ControlSysexMsg()
{
}

constexpr int32_t ControlSysexMsg::LENGTH;

bool ControlSysexMsg::isControl(const vector<char>& data)
{
    return (static_cast<unsigned char>(data[0]) == SYSTEM_EXCLUSIVE) && (data[1] == ID_NON_COMMERCIAL) && data.size() == LENGTH;
}

const vector<char> ControlSysexMsg::createControl(int32_t providerId, int32_t moduleId, int32_t instanceIndex, int32_t controlId, int32_t value)
{

	if (instanceIndex > 7) {
		/*
		throw new ::javax::sound::midi::InvalidMidiDataException(::java::lang::StringBuilder().append(u"Instance index "_j)->append(instanceIndex)
			->append(u" MUST be < 8"_j)->toString());
			*/
		return {};
	}

	auto data = vector<char>(LENGTH);
    data[0] = static_cast<char>(SYSTEM_EXCLUSIVE);
    data[1] = ID_NON_COMMERCIAL;
    data[2] = static_cast<int8_t>(providerId & 127);
    data[3] = static_cast<int8_t>(moduleId & 127);
    data[4] = static_cast<int8_t>(instanceIndex & 7);
    data[5] = static_cast<int8_t>(controlId & 127);
    data[6] = static_cast<int8_t>(value & 127);
    data[7] = static_cast<int8_t>((value >> 7) & 127);
	return data;
}

int32_t ControlSysexMsg::getProviderId(const std::vector<char>& data)
{
    return data[2] & int32_t(127);
}

int32_t ControlSysexMsg::getModuleId(const std::vector<char>& data)
{
    return data[3] & int32_t(127);
}

int32_t ControlSysexMsg::getInstanceIndex(const std::vector<char>& data)
{
    return data[4] & int32_t(7);
}

int32_t ControlSysexMsg::getControlId(const std::vector<char>& data)
{
    return data[5] & int32_t(127);
}

int32_t ControlSysexMsg::getValue(const std::vector<char>& data)
{
    return data[6] + int32_t(128) * data[7];
}
