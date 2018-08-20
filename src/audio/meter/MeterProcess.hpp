#pragma once

#include <audio/core/SimpleAudioProcess.hpp>

#include <vector>
#include <memory>

namespace ctoot {
	namespace audio {
		namespace meter {

			class MeterControls;

			class MeterProcess
				: public ctoot::audio::core::SimpleAudioProcess
			{

			private:
				std::weak_ptr<MeterControls> controls{  };
				float bufferTime{ -1.0f };

			public:
				int processAudio(::ctoot::audio::core::AudioBuffer* buffer) override;

			private:
				void check(::ctoot::audio::core::AudioBuffer* buffer);

			protected:
				void detectOvers(int chan, std::vector<float>* samples, int len);
				void detectPeak(int chan, std::vector<float>* samples, int len);
				void detectAverage(int chan, std::vector<float>* samples, int len);

			public:
				MeterProcess(std::weak_ptr<MeterControls> controls);

			};

		}
	}
}
