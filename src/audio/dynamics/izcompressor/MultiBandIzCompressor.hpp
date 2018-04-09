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

				class MultiBandIzControls;
				class IzCompressor;

				class MultiBandIzCompressor
					: public virtual ctoot::audio::core::AudioProcess
				{

				private:
					MultiBandIzControls * multiBandControls{  };
					std::vector<IzCompressor*> compressors{  };
					ctoot::audio::filter::Crossover* midXO{ nullptr };
					ctoot::audio::filter::Crossover* hiXO{ nullptr };
					ctoot::audio::filter::Crossover* loXO{ nullptr };
					std::vector<ctoot::audio::core::AudioBuffer*> bandBuffers{  };
					int32_t nbands{  };
					int32_t nchans{ -1 };
					int32_t nsamples{ -1 };
					int32_t sampleRate{ -1 };
					bool wasBypassed{  };

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
					MultiBandIzCompressor(MultiBandIzControls* c);
					~MultiBandIzCompressor();

				};

			}
		}
	}
}
