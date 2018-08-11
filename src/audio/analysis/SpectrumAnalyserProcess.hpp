#include <audio/core/AudioProcess.hpp>

#include <vector>
#include <memory>

namespace ctoot {

	namespace audio {

		namespace core {
			class AudioBuffer;
		}

		namespace analysis {

			class SpectrumAnalyserControl;

			class SpectrumAnalyserProcess
				: public audio::core::AudioProcess
			{

			private:
				std::weak_ptr<SpectrumAnalyserControl> control;

			public:
				int getBandCount();

			public:
				int processAudio(ctoot::audio::core::AudioBuffer* buffer) override;
				void open() override {};
				void close() override {};

			public:
				SpectrumAnalyserProcess(std::weak_ptr<SpectrumAnalyserControl> control);
				~SpectrumAnalyserProcess();

			};
		}
	}
}
