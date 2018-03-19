#pragma once
#include <audio/filter/FilterState.hpp>

namespace ctoot {
	namespace audio {
		namespace filter {

			class BiQuadState
				: public virtual FilterState
			{

			public:
				float x1{  };
				float x2{  };
				float y1{  };
				float y2{  };

			public:
				void clear() override;

			public:
				BiQuadState();
			};

		}
	}
}
