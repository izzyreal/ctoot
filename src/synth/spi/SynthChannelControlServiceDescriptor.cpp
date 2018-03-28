#include <synth/spi/SynthChannelControlServiceDescriptor.hpp>

using namespace ctoot::synth::spi;
using namespace std;

SynthChannelControlServiceDescriptor::SynthChannelControlServiceDescriptor(string typeIdName, int32_t moduleId, string name, string description, string version)
	: ctoot::control::spi::ControlServiceDescriptor(typeIdName, moduleId, name, description, version)
{
}
