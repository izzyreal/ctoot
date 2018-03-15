#include "AudioControlsChain.hpp"

#include "AudioControls.hpp"
#include "Descriptors.hpp"
#include "AudioServices.hpp"
#include "ChannelFormat.hpp"

#include <service/ServiceDescriptor.hpp>

//#include <audio/spi/AudioControlServiceDescriptor.hpp>
//
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


bool AudioControlsChain::isCompatibleDescriptor(ctoot::service::ServiceDescriptor* d) {
	// !!! nasty heuristic so reverbs only appear in FX strips
	//if (d.getDescription().equals(getString("Reverb")) && getName().indexOf("FX") < 0) {
		//return false;
	//}
	if (!constraintChannelFormat.lock()) return true; // we're not fixed format
	/*
	if (d instanceof AudioControlServiceDescriptor) {
		AudioControlServiceDescriptor acsd =
			(AudioControlServiceDescriptor)d;
		ChannelFormat descriptorFormat = acsd.getChannelFormat();
		if (descriptorFormat == null) return true; // plugin can cope
		if (descriptorFormat.getCount() > constraintChannelFormat.getCount()) {
			return false;
		}
	}
	*/
	return true;
}

void AudioControlsChain::setMetaInfo(weak_ptr<MetaInfo> wMetaInfo)
{
	/*
	auto metaInfo = wMetaInfo.lock();
	if(metaInfo != nullptr) {
		sourceLabel = metaInfo->getSourceLabel();
		sourceLocation = metaInfo->getSourceLocation();
    } else {
		sourceLabel = "";
        sourceLocation = "";
    }
    setChanged();
	notifyObservers();
	*/
}

string ctoot::audio::core::AudioControlsChain::getSourceLabel()
{
    return sourceLabel;
}

string ctoot::audio::core::AudioControlsChain::getSourceLocation()
{
    return sourceLocation;
}


weak_ptr<ChannelFormat> ctoot::audio::core::AudioControlsChain::getConstraintChannelFormat()
{
    return constraintChannelFormat;
}

shared_ptr<ctoot::control::CompoundControl> AudioControlsChain::createControl(string name)
{
	return AudioServices::createControls(name);
}

int ctoot::audio::core::AudioControlsChain::getMaxInstance()
{
    return 1024 - 1;
}

string ctoot::audio::core::AudioControlsChain::getPersistenceDomain()
{
	return "audio";
}

AudioControlsChain::~AudioControlsChain() {
}
