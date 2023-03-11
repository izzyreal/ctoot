#include "AudioControlsChain.hpp"

#include "AudioControls.hpp"
#include "AudioServices.hpp"

#include <service/ServiceDescriptor.hpp>

using namespace ctoot::audio::core;
using namespace ctoot::control;

AudioControlsChain::AudioControlsChain(int id, std::string name)
	: CompoundControlChain(id, name)
{
}

AudioControlsChain::AudioControlsChain(int id, int index, std::string name)
	: CompoundControlChain(id, index, name)
{
}

std::shared_ptr<ctoot::control::CompoundControl> AudioControlsChain::createControl(std::string name)
{
    
	return AudioServices::createControls(name);
}

int ctoot::audio::core::AudioControlsChain::getMaxInstance()
{
    return 1024 - 1;
}

AudioControlsChain::~AudioControlsChain() {
}
