#pragma once
#include <audio/core/FloatSampleBuffer.hpp>

#include <string>

#include <memory>

namespace ctoot::audio::core
{
	class ChannelFormat;

	class AudioBuffer
		: public FloatSampleBuffer
	{

	private:
		std::weak_ptr<ChannelFormat> channelFormat;
		bool realTime{ true };
		std::string name{ "" };

	public:
		std::string getName();

	protected:
		void setChannelCount(int count);

	public:
		bool isRealTime();
		void setRealTime(bool realTime);

	public:
		std::weak_ptr<ChannelFormat> guessFormat();

	public:
		std::weak_ptr<ChannelFormat> getChannelFormat();
		void setChannelFormat(std::weak_ptr<ChannelFormat> format);

        void convertTo(std::weak_ptr<ChannelFormat> format);
		void swap(int a, int b);
		float square();

        void copyFrom(AudioBuffer* src);
		const bool isSilent();

	public:
		AudioBuffer(std::string name, int channelCount, int sampleCount, float sampleRate);
		~AudioBuffer();

	};
}
