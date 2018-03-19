#include <audio/dynamics/MultiBandControls.hpp>

#include <audio/dynamics/DynamicsIds.hpp>

using namespace ctoot::audio::dynamics;

MultiBandControls::MultiBandControls(std::string name)
	: ctoot::audio::core::AudioControls(DynamicsIds::MULTI_BAND_COMPRESSOR_ID, name)
{
}

bool MultiBandControls::hasOrderedFrequencies()
{
    return true;
}
