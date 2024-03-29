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
				void setSourceLocation(std::string sourceLocation);

			public:
				std::string getSourceLabel();
				std::string getSourceLocation();

			public:
				MetaInfo(std::string sourceLabel, std::string sourceLocation);
				MetaInfo(std::string _sourceLabel) : MetaInfo(_sourceLabel, "") {};

			};

		}
	}
}
