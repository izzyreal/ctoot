#pragma once

#include <midi/message/MidiMsg.hpp>

namespace ctoot {
	namespace midi {
		namespace message {

			class SysexMsg
				: public MidiMsg
			{

			public:
				static bool isSysex(ctoot::midi::core::MidiMessage* msg);
				static bool isSysex(int status);
				static ctoot::midi::core::MidiMessage* createSysex(const std::vector<char>& data, int length);
				static constexpr int32_t SYSTEM_EXCLUSIVE{ int32_t(240) };
				static constexpr int32_t SPECIAL_SYSTEM_EXCLUSIVE{ int32_t(247) };
				static constexpr int32_t END_OF_EXCLUSIVE{ int32_t(247) };
				static constexpr int32_t ID_NON_COMMERCIAL{ int32_t(125) };

			public:
				SysexMsg();
			};

		}
	}
}
