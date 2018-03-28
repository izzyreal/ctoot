#include <synth/modules/filter/MoogFilterControls.hpp>

#include <synth/modules/filter/FilterIds.hpp>

using namespace ctoot::synth::modules::filter;

MoogFilterControls::MoogFilterControls(int32_t instanceIndex, std::string name, int32_t idOffset)
	: FilterControls(FilterIds::MOOG_LPF_ID, instanceIndex, name, idOffset)
{
}

float MoogFilterControls::deriveResonance()
{
    return FilterControls::deriveResonance() * 4;
}
