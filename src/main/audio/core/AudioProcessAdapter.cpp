#include <audio/core/AudioProcessAdapter.hpp>
#include <audio/core/AudioProcess.hpp>

#include <stdexcept>

using namespace ctoot::audio::core;

AudioProcessAdapter::AudioProcessAdapter(AudioProcess* process)
{
	if (process == nullptr)
		throw new std::invalid_argument("AudioProcessAdapter process == nullptr");
    
	this->process = process;
}

int AudioProcessAdapter::processAudio(AudioBuffer* buf, int nFrames)
{
	return process->processAudio(buf, nFrames);
}
