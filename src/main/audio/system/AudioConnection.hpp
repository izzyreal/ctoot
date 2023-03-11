#pragma once

#include <string>

namespace ctoot {
	namespace audio {
		namespace system {

			class AudioConnection

			{

            public:
                AudioConnection(int flags);
                virtual ~AudioConnection() {}

			public:
				static const int PLAYBACK{ 1 };
				static const int SYSTEM{ 2 };

            private:
				int flags{ 0 };

			public:
				virtual void close() = 0;
				virtual std::string getOutputName() = 0;
				virtual std::string getOutputLocation() = 0;

            };

		}
	}
}
