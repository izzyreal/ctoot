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

int ctoot::audio::core::AudioControlsChain::getMaxInstance()
{
    return 1024 - 1;
}
