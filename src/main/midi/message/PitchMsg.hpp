#pragma once
#include <midi/message/ChannelMsg.hpp>

namespace ctoot {
	namespace midi {
		namespace message {

			class PitchMsg
				: public ChannelMsg
			{

			public:
				typedef ChannelMsg super;

                static ctoot::midi::core::MidiMessage* transpose(ctoot::midi::core::MidiMessage* msg, int semitones);
				static int getPitch(ctoot::midi::core::MidiMessage* msg);

                PitchMsg();
			};
	
		}
	}
}