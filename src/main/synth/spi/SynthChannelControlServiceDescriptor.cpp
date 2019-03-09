#include <synth/spi/SynthChannelControlServiceDescriptor.hpp>

using namespace ctoot::synth::spi;
using namespace std;

SynthChannelControlServiceDescriptor::SynthChannelControlServiceDescriptor(
	const string& typeIdName, 
	int32_t moduleId, 
	const string& name,
	const string& description,
	const string& version)
	: ctoot::control::spi::ControlServiceDescriptor(typeIdName, moduleId, name, description, version)
{
}
