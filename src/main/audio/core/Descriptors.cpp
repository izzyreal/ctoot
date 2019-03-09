#include <audio/core/Descriptors.hpp>

using namespace ctoot::audio::core;
using namespace std;

Descriptors::Descriptors(AudioControlsChain *AudioControlsChain_this, vector<ServiceDescriptor>* descriptors)
    :  AudioControlsChain_this(AudioControlsChain_this)
{
}

void Descriptors::visitDescriptor(ServiceDescriptor* d)
{
    if (AudioControlsChain_this->isCompatibleDescriptor(d)) {
		descriptors.push_back(d);
	 }
}