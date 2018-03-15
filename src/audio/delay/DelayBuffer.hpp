#pragma once

#include <audio/core/FloatSampleBuffer.hpp>


namespace ctoot {
	namespace audio {
		namespace delay {

			class DelayBuffer_Filter;

			class DelayBuffer
				: public ctoot::audio::core::FloatSampleBuffer
			{

			public:
				float lowpassK{ 1.0f };

			private:
				int writeIndex{ 0 };
				int readIndex{ 0 };
				std::vector<float> apzm1;
				std::vector<DelayBuffer_Filter*> lowpass{  };

			public:
				virtual void nudge(int on);
				virtual void append(int chan, float value);
				virtual void append(ctoot::audio::core::FloatSampleBuffer* source);
				virtual void append(ctoot::audio::core::FloatSampleBuffer* source1, ctoot::audio::core::FloatSampleBuffer* source2, float level2);
				virtual void appendFiltered(ctoot::audio::core::FloatSampleBuffer* source1, ctoot::audio::core::FloatSampleBuffer* source2, float level2, float k);
				virtual float outU(int chan, int delay);
				virtual float out(int chan, float delay);
				virtual float outA(int chan, float delay);
				virtual void tap(ctoot::audio::core::FloatSampleBuffer* buf, int delay, float weight);
				virtual void tap(int ch, ctoot::audio::core::FloatSampleBuffer* buf, int delay, float weight);
				virtual void conform(ctoot::audio::core::FloatSampleBuffer* buf);
				virtual float msToSamples(float ms);

			public:
				DelayBuffer(int channelCount, int sampleCount, float sampleRate);
				~DelayBuffer();
			};
		}
	}
}
