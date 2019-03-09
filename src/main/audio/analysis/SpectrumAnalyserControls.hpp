#include <audio/core/AudioControls.hpp>


namespace ctoot {

	namespace audio {
	
		namespace analysis {

			class SpectrumAnalyserControls
				: public audio::core::AudioControls
			{

			private:
				std::vector<float> values;
				int min = -140;
				int max = 40;
				float sampleRate = 0;

			private:
				void setValues(const std::vector<float>& values);
				void setValue(const int index, const float value);

			public:
				std::vector<float>* getValues();
				void setRangeMin(int min);
				void setRangeMax(int max);
				int getRangeMin();
				int getRangeMax();
				void setSampleRate(float sr);
				float getSampleRate();

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
