#pragma once

#include <audio/core/FloatSampleBuffer.hpp>

using namespace ctoot::audio::core;

namespace ctoot {
	namespace audio {
		namespace delay {

			class DelayBufferFilter;

			class DelayBuffer
				: public FloatSampleBuffer
			{

			public:
				float lowpassK{ 1.0f };

			private:
				int writeIndex{ 0 };
				int readIndex{ 0 };
				std::vector<float> apzm1;
				std::vector<DelayBufferFilter*> lowpass{  };

			public:
				virtual void nudge(int on);
				virtual void append(int chan, float value);
				virtual void append(FloatSampleBuffer* source);
				virtual void append(FloatSampleBuffer* source1, FloatSampleBuffer* source2, float level2);
				virtual void appendFiltered(FloatSampleBuffer* source1, FloatSampleBuffer* source2, float level2, float k);
				virtual float outU(int chan, int delay);
				virtual float out(int chan, float delay);
				virtual float outA(int chan, float delay);
				virtual void tap(FloatSampleBuffer* buf, int delay, float weight);
				virtual void tap(int ch, FloatSampleBuffer* buf, int delay, float weight);
				virtual void conform(FloatSampleBuffer* buf);
				virtual float msToSamples(float ms);

			public:
				DelayBuffer(int channelCount, int sampleCount, float sampleRate);
				virtual ~DelayBuffer();
			};
		}
	}
}
