#pragma once

#include <audio/core/AudioProcess.hpp>

namespace ctoot {
	namespace audio {

		namespace core {
			class AudioBuffer;
		}

		namespace filter {
			class Crossover;
		}

		namespace dynamics {

			class CrossoverControl;

			namespace izcompressor {

				class IzMultiBandControls;
				class IzCompressor;

				class IzMultiBandCompressor
					: public virtual ctoot::audio::core::AudioProcess
				{

				private:
					IzMultiBandControls * multiBandControls{  };
					std::vector<IzCompressor*> compressors{  };
					ctoot::audio::filter::Crossover* midXO{ nullptr };
					ctoot::audio::filter::Crossover* hiXO{ nullptr };
					ctoot::audio::filter::Crossover* loXO{ nullptr };
					ctoot::audio::filter::Crossover* kmidXO{ nullptr };
					ctoot::audio::filter::Crossover* khiXO{ nullptr };
					ctoot::audio::filter::Crossover* kloXO{ nullptr };
					std::vector<ctoot::audio::core::AudioBuffer*> bandBuffers{  };
					std::vector<ctoot::audio::core::AudioBuffer*> keyBuffers{  };
					int32_t nbands{  };
					int32_t nchans{ -1 };
					int32_t nsamples{ -1 };
					int32_t sampleRate{ -1 };
					bool wasBypassed{  };
					float smoothedInputGain{ 1.0f };
					float smoothedOutputGain{ 1.0f };

				public:
					void open() override;
					void close() override;
					virtual void clear();
					int32_t processAudio(ctoot::audio::core::AudioBuffer* buffer) override;

				protected:
					virtual void conformBandBuffers(ctoot::audio::core::AudioBuffer* buf);
					virtual void split(ctoot::audio::filter::Crossover* xo, ctoot::audio::core::AudioBuffer* source, ctoot::audio::core::AudioBuffer* low, ctoot::audio::core::AudioBuffer* high);
					virtual ctoot::audio::filter::Crossover* createCrossover(CrossoverControl* c);
					virtual void updateSampleRate(int32_t rate);

				public:
					IzMultiBandCompressor(IzMultiBandControls* c);
					~IzMultiBandCompressor();

				};

			}
		}
	}
}
