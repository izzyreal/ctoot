#include "AudioControlsChain.hpp"

#include "AudioControls.hpp"
#include "AudioServices.hpp"
#include "ChannelFormat.hpp"

#include <service/ServiceDescriptor.hpp>

//#include <audio/spi/AudioControlServiceDescriptor.hpp>
//#include <service/ServiceDescriptor.hpp>


using namespace ctoot::audio::core;
//using namespace ctoot::audio::spi;
using namespace ctoot::control;
using namespace std;

AudioControlsChain::AudioControlsChain(int id, string name)
	: CompoundControlChain(id, name)
{
}

AudioControlsChain::AudioControlsChain(int id, int index, string name, weak_ptr<ChannelFormat> constraintFormat)
	: CompoundControlChain(id, index, name)
{
	constraintChannelFormat = constraintFormat;
}

shared_ptr<ctoot::control::CompoundControl> AudioControlsChain::createControl(string name)
{
    
	return AudioServices::createControls(name);
}

int ctoot::audio::core::AudioControlsChain::getMaxInstance()
{
    return 1024 - 1;
}

AudioControlsChain::~AudioControlsChain() {
}
