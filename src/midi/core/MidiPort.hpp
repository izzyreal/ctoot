#pragma once

#include <string>

namespace ctoot {
	namespace midi {
		namespace core {


			class MidiPort

			{
			public:
				virtual std::string getName() = 0;

			};

		}
	}
}
