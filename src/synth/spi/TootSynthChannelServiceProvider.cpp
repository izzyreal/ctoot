#include <synth/spi/TootSynthChannelServiceProvider.hpp>

#include <control/id/ProviderId.hpp>

using namespace ctoot::synth::spi;

TootSynthChannelServiceProvider::TootSynthChannelServiceProvider(std::string description, std::string version)
	: SynthChannelServiceProvider(ctoot::control::id::ProviderId::TOOT_PROVIDER_ID, "Toot Software", description, version)
{
}
