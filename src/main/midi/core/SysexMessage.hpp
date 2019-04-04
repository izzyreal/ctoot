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
				static constexpr int32_t SPECIAL_SYSTEM_EXCLUSIVE{ int32_t(247) };
				static constexpr int32_t SYSTEM_EXCLUSIVE{ int32_t(240) };

			public:
				const std::vector<char> getData();
				//void setMessage(std::vector<char> data, int length) override;

				SysexMessage();

			protected:
				SysexMessage(const std::vector<char>& data);

			public:
				SysexMessage(const std::vector<char>& data, int32_t length);
			};

		}
	}
}
