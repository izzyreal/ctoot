#include <control/FloatVectorControl.hpp>


namespace ctoot {

	namespace audio {
	
		namespace analysis {

			class SpectrumAnalyserControl
				: public ctoot::control::FloatVectorControl
			{

			private:
				int bandCount = 16;

			public:
				void setBandCount(int count);

			public:
				SpectrumAnalyserControl();
				~SpectrumAnalyserControl();

			};
		}
	}
}
