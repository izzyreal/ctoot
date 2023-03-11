#pragma once
#include <string>

namespace ctoot {
	namespace audio {
		namespace core {

			class MetaInfo
			{

			private:
				std::string sourceLabel = { "" };
				std::string sourceLocation = { "" };

            public:
				MetaInfo(std::string sourceLabel, std::string sourceLocation);
				MetaInfo(std::string _sourceLabel) : MetaInfo(_sourceLabel, "") {};

			};

		}
	}
}
