#pragma once

#include <audio/core/AudioBuffer.hpp>

#include <string>
#include <cstdint>
#include <vector>
#include <memory>

namespace ctoot {
	namespace audio {
		namespace core {
            
			class ChannelFormat
			{

			public:
				virtual int getCount() = 0;
				virtual int getCenter() = 0;
				virtual int getLFE() = 0;
				virtual std::vector<int8_t> getLeft() = 0;
				virtual std::vector<int8_t> getRight() = 0;
				virtual std::string getName() = 0;

                virtual std::string getName(int chan) = 0;

			public:
				int mix(ctoot::audio::core::AudioBuffer* destBuffer, ctoot::audio::core::AudioBuffer* sourceBuffer, std::vector<float>& gain);

			public:
				static std::weak_ptr<ChannelFormat> MONO();
				static std::weak_ptr<ChannelFormat> STEREO();
				static std::weak_ptr<ChannelFormat> QUAD();
				static std::weak_ptr<ChannelFormat> FIVE_1();

			public:
				ChannelFormat();

			};

		}
	}
}
