#pragma once
#include <audio/mixer/LCRControl.hpp>

namespace ctoot {
	namespace audio {
		namespace mixer {

			class BalanceControl
				: public LCRControl
			{

			private:
				float left{ 1 };
				float right{ 1 };

			public:
				float getLeft() override;
				float getRight() override;
				void setValue(float value) override;

			public:
				BalanceControl();
				virtual ~BalanceControl();

			};
	
		}
	}
}
