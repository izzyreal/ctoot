#pragma once

#include <synth/SynthChannel.hpp>
#include <audio/system/AudioOutput.hpp>

#include <memory>

namespace ctoot {
	namespace synth {
		class MonophonicSynthChannel
			: public SynthChannel
			, public virtual ctoot::audio::system::AudioOutput
		{

		private:
			std::shared_ptr<ctoot::audio::core::MetaInfo> info;
			std::string location{  };
			std::string name{  };
			int32_t noteCount{ 0 };
			float frequency{  };
			float targetFrequency{  };
			bool gliding{ false };
			float glideFactor{  };
			int32_t sampleCount{ 256 };

		protected:
			float amplitude{  };
			float semitones{  };

		private:
			float targetSemitones{  };
			float semitoneIncrement{  };

		public:
			std::string getName() override;
			void setLocation(std::string location) override;
			std::string getLocation() override;
			void noteOn(int32_t pitch, int32_t velocity) override;
			void noteOff(int32_t pitch) override;
			void open() override;
			int32_t processAudio(ctoot::audio::core::AudioBuffer* buffer) override;
			void close() override;

		private:
			void glide();

		public:
			void allNotesOff() override;
			void allSoundOff() override;

		protected:
			virtual bool isComplete() = 0;
			virtual void trigger(float amp) = 0;
			virtual void release() = 0;
			virtual void update(float frequency) = 0;
			virtual float getSample() = 0;
			virtual bool isGlideEnabled() = 0;
			virtual int32_t getGlideMilliseconds() = 0;

		public:
			MonophonicSynthChannel(std::string name);

		public:
			void noteOff(int32_t pitch, int32_t velocity);

		};

	}
}
