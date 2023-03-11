#pragma once

#include "MidiMessage.hpp"

#include <stdint.h>

namespace ctoot {

	namespace midi {
		namespace core {

			class SysexMessage
				: public MidiMessage
			{

			public:
				typedef MidiMessage super;

            public:
				const std::vector<char> getData();
				//void setMessage(std::vector<char> data, int length) override;

				SysexMessage();

            };

		}
	}
}
