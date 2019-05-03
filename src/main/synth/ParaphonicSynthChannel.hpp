#pragma once

#include <synth/PolyphonicSynthChannel.hpp>
#include <audio/system/AudioOutput.hpp>

namespace ctoot {

	namespace synth {

		class ParaphonicSynthChannel
			: public PolyphonicSynthChannel
			, public virtual ctoot::audio::system::AudioOutput
		{

		public:
			int32_t processAudio(ctoot::audio::core::AudioBuffer* buffer) override;

		protected:
			virtual int32_t postProcessAudio(ctoot::audio::core::AudioBuffer* buffer, int32_t ret) = 0;

		public:
			ParaphonicSynthChannel(std::string name);

		public:
			virtual void close() override;
			virtual void open() override;
            virtual std::string getLocation() override;
			virtual std::string getName() override;

		};

	}
}
