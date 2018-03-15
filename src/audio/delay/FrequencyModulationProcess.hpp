#pragma once

#include <audio/core/AudioProcess.hpp>
#include <audio/core/ChannelFormat.hpp>

#include <vector>

namespace ctoot {
	namespace audio {
		namespace delay {

			class DelayBuffer;
			class DelayVariables;

			class FrequencyModulationProcess
				: public virtual ctoot::audio::core::AudioProcess
			{

			private:
				DelayBuffer * delayBuffer{};
				DelayVariables* vars{};
				std::vector<std::vector<float>*> samples{};

			protected:
				ctoot::audio::core::ChannelFormat* format{};
				int sampleRate{};

			private:
				bool wasBypassed{};
				float maxDelayMillis{};
				int staticDelay{};

			public:
				void open() override;

			public:
				virtual void cacheProcessVariables();
				virtual void sampleRateChanged();

			public:
				int processAudio(ctoot::audio::core::AudioBuffer* buffer) override;
				void close() override;

			protected:
				virtual int msToSamples(float ms, float sr);
				virtual float modulation() = 0;

			public:
				FrequencyModulationProcess(DelayVariables* vars);

			};

		}
	}
}
