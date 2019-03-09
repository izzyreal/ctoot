#pragma once
#include <audio/core/FloatSampleBuffer.hpp>
#include <audio/core/MetaInfo.hpp>

#include <string>

#include <memory>

namespace ctoot {
	namespace audio {
		namespace core {
            
            class ChannelFormat;

			class AudioBuffer
				: public FloatSampleBuffer
			{

			private:
				std::weak_ptr<MetaInfo> metaInfo;
				std::weak_ptr<ChannelFormat> channelFormat;
				bool realTime{ true };
				std::string name{ "" };

			public:
				std::string getName();

			protected:
				void setChannelCount(int count);

			public:
				void setMetaInfo(std::weak_ptr<MetaInfo> info);
				std::weak_ptr<MetaInfo> getMetaInfo();
				bool isRealTime();
				void setRealTime(bool realTime);

			public:
				std::weak_ptr<ChannelFormat> guessFormat();

			public:
				std::weak_ptr<ChannelFormat> getChannelFormat();
				void setChannelFormat(std::weak_ptr<ChannelFormat> format);
				void monoToStereo();
				void convertTo(std::weak_ptr<ChannelFormat> format);
				void swap(int a, int b);
				float square();
				bool encodeMidSide();
				bool decodeMidSide();
				void copyFrom(AudioBuffer* src);

			public:
				AudioBuffer(std::string name, int channelCount, int sampleCount, float sampleRate);
				~AudioBuffer();

			};

		}
	}
}
