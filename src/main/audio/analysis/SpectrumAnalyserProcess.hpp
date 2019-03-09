#include <audio/core/AudioProcess.hpp>

#include <io/StereoCircularTBuffer.hpp>

#include <thirdp/fftreal/FFTReal.h>

#include <vector>
#include <memory>

namespace ctoot {

	namespace audio {

		namespace core {
			class AudioBuffer;
		}

		namespace analysis {

			class SpectrumAnalyserControls;

			class SpectrumAnalyserProcess
				: public audio::core::AudioProcess
			{

			private:
				static const int FFT_SIZE = 2048;

			private:
				std::weak_ptr<SpectrumAnalyserControls> controls;
				int sampleRate = 0;
				std::unique_ptr<moduru::io::StereoCircularTBuffer> circBuf;
				std::unique_ptr<FFTReal> fft;

			public:
				int processAudio(ctoot::audio::core::AudioBuffer* buffer) override;
				void open() override {};
				void close() override {};

			public:
				SpectrumAnalyserProcess(std::weak_ptr<SpectrumAnalyserControls> controls);
				~SpectrumAnalyserProcess();

			};
		}
	}
}
