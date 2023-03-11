#include <synth/spi/TootSynthChannelServiceProvider.hpp>

using namespace ctoot::synth::spi;

TootSynthChannelServiceProvider::TootSynthChannelServiceProvider(std::string description, std::string version)
	: SynthChannelServiceProvider("Toot Software", description, version)
{
}
