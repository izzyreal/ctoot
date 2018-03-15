#pragma once

#include <string>

namespace ctoot {
	namespace audio {
		namespace delay {

			class NamedFactor
				
			{

			private:
				float factor{  };
				std::string name{  };

			public:
				virtual float getFactor();
				std::string toString();
				
				NamedFactor(float factor, std::string name);
				
			};

		}
	}
}
