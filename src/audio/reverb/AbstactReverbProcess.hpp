#pragma once
#include <audio/core/SimpleAudioProcess.hpp>
#include <audio/core/AudioBuffer.hpp>

#include "MVerb.hpp"

#include <vector>

namespace ctoot {
	namespace audio {
		namespace reverb {

			class AbstractReverbProcess
				: public core::SimpleAudioProcess
			{
			private:
				MVerb<float> em_verb;

			public:
				int processAudio(core::AudioBuffer* buffer) override;

			protected:
				virtual void cacheVariables() = 0;
				virtual void reverb(float left, float right) = 0;
				virtual float left() = 0;
				virtual float right() = 0;

			};

			class Filter
			{
			private:
				float zm1 = 0;
			
			public:
				float filter(float sample, float k);

			};

			class Delay
			{
			private:
				std::vector<float> line;
				int head = 0;
				int length;
				int maxLength;

			public:
				float read();
				void append(float sample);
				float delay(float sample);
				float tap(int zm);
				void resize(float factor);

			public:
				Delay();
				Delay(int length);
			};

			class Diffuser
				: public Delay			
			{
			private:
				float b = 0;
				
			public:
				Diffuser();
				Diffuser(int length);

			public:
				float diffuse(float sample, float k);
				float diffuse2(float sample, float k);
			};
		}
	}
}
