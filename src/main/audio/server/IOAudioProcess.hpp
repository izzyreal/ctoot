#pragma once
#include <audio/core/AudioProcess.hpp>

#include <vector>

namespace ctoot::audio::server
{
	class IOAudioProcess
		: public virtual ctoot::audio::core::AudioProcess
	{
	public:
		std::vector<float> localBuffer;
		virtual std::weak_ptr<ctoot::audio::core::ChannelFormat> getChannelFormat() = 0;
		virtual std::string getName() = 0;

	};
}
