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
			class MultiBandControls;
			class Compressor;

			class MultiBandCompressor
				: public virtual ctoot::audio::core::AudioProcess
			{

			private:
				MultiBandControls* multiBandControls{  };
				std::vector<Compressor*> compressors{  };
				ctoot::audio::filter::Crossover* midXO{  };
				ctoot::audio::filter::Crossover* hiXO{  };
				ctoot::audio::filter::Crossover* loXO{  };
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
				MultiBandCompressor(MultiBandControls* c);

			};

		}
	}
}