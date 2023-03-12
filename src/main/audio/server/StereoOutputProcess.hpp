#include <audio/server/AudioServerProcess.hpp>

#include <audio/core/AudioBuffer.hpp>

namespace ctoot::audio::server
{
	class StereoOutputProcess
		: public AudioServerProcess
	{

	public:
		int processAudio(ctoot::audio::core::AudioBuffer* buffer, int nFrames) override;
		StereoOutputProcess(std::string name);

	};
}
