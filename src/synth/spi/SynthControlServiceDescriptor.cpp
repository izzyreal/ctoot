#include <synth/spi/SynthControlServiceDescriptor.hpp>

using namespace ctoot::synth::spi;

SynthControlServiceDescriptor::SynthControlServiceDescriptor(std::string typeIdName, int32_t moduleId, std::string name, std::string description, std::string version)
	: ctoot::control::spi::ControlServiceDescriptor(typeIdName, moduleId, name, description, version)
{
}
