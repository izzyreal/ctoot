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

				static const unsigned char SYSTEM_EXCLUSIVE{ 240 };
				static const unsigned char SPECIAL_SYSTEM_EXCLUSIVE{ 247 };
				static const unsigned char END_OF_EXCLUSIVE{ 247 };
				static const unsigned char ID_NON_COMMERCIAL{ 125 };

			public:
				SysexMsg();
			};

		}
	}
}
