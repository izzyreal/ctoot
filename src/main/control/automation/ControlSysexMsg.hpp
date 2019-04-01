#pragma once

#include <midi/message/SysexMsg.hpp>

#include <stdint.h>

namespace ctoot {
	namespace control {
		namespace automation {

			class ControlSysexMsg
				: public ctoot::midi::message::SysexMsg
			{

			public:
				typedef ctoot::midi::message::SysexMsg super;

			private:
				static constexpr int32_t LENGTH{ int32_t(8) };

			public:
				//static bool isControl(::javax::sound::midi::MidiMessage* msg);
				static bool isControl(const std::vector<char>& data);
				static const std::vector<char> createControl(int32_t providerId, int32_t moduleId, int32_t instanceIndex, int32_t controlId, int32_t value);
				static int32_t getProviderId(const std::vector<char>& data);
				static int32_t getModuleId(const std::vector<char>& data);
				static int32_t getInstanceIndex(const std::vector<char>& data);
				static int32_t getControlId(const std::vector<char>& data);
				static int32_t getValue(const std::vector<char>& data);

			public:
				ControlSysexMsg();
			};

		}
	}
}
