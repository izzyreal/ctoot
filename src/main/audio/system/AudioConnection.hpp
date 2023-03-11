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
