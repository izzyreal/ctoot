#include <audio/core/AudioControls.hpp>


namespace ctoot {

	namespace audio {
	
		namespace analysis {

			class SpectrumAnalyserControls
				: public audio::core::AudioControls
			{

			private:
				int bandCount = 16;

			public:
				void setBandCount(int count);

			private:
				std::vector<float> values;

			private:
				void setValues(const std::vector<float>& values);
				void setValue(const int index, const float value);

			public:
				std::vector<float>* getValues();

			public:
				SpectrumAnalyserControls();
				~SpectrumAnalyserControls();

			private:
				friend class SpectrumAnalyserProcess;

			};

			REGISTER_TYPE(ctoot::audio::analysis::, SpectrumAnalyserControls)
		}
	}
}
