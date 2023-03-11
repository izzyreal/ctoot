#include <audio/mixer/MixerControls.hpp>

#include <control/id/ProviderId.hpp>
#include <audio/mixer/BusControls.hpp>
#include <audio/core/ChannelFormat.hpp>

//#include <audio/id/ProviderId.hpp>
#include <audio/mixer/GainControl.hpp>
#include <audio/mixer/MixerControlsFactory.hpp>
#include <audio/mixer/MixerControlsIds.hpp>
#include <control/CompoundControl.hpp>
#include <control/Control.hpp>

#include <algorithm>

using namespace ctoot::audio::mixer;
using namespace ctoot::audio::core;
using namespace ctoot::audio::fader;
using namespace std;

MixerControls::MixerControls(string name, string mainBusName, weak_ptr<ChannelFormat> channelFormat)
	: CompoundControl(1, name)
{
	mainBusControls = make_shared<BusControls>(MixerControlsIds::MAIN_BUS, mainBusName, channelFormat.lock());
}

int MixerControls::getProviderId()
{
    return control::id::ProviderId::TOOT_PROVIDER_ID;
}

float MixerControls::getSmoothingFactor()
{
    return smoothingFactor;
}

void MixerControls::createAuxBusControls(string name, weak_ptr<ChannelFormat> format)
{
	if (!canAddBusses) {
		return;
	}
	auto busControls = make_shared<BusControls>(MixerControlsIds::AUX_BUS, name, format.lock());
	auxBusControls.push_back(std::move(busControls));
}

weak_ptr<BusControls> MixerControls::getBusControls(string name)
{
	auto mbc = mainBusControls;
	
	auto mbcName = mbc->getName();

	if (std::mismatch(mbcName.begin(), mbcName.end(), name.begin()).first == mbcName.end()) {
		return mainBusControls;
	}

	for (int i = 0; i < auxBusControls.size(); i++) {
		auto busControls = auxBusControls[i];
		if (busControls->getName().compare(name) == 0) {
			return busControls;
		}
	}
	return {};
}

weak_ptr<BusControls> MixerControls::getMainBusControls()
{
	return mainBusControls;
}

vector<shared_ptr<BusControls>> MixerControls::getAuxBusControls()
{
	return auxBusControls;
}

weak_ptr<AudioControlsChain> MixerControls::createStripControls(int id, int index, string name)
{
    return createStripControls(id, index, name, true);
}

weak_ptr<AudioControlsChain> MixerControls::createStripControls(int id, int index, string name, bool hasMixControls)
{
	if (getStripControls(name).lock()) {
		string error = name.append(" already exists");
		MLOG("ERROR: " + error);
		return {};
	}
	auto chain = std::make_shared<AudioControlsChain>(id, index, name);
	MixerControlsFactory::addMixControls(this, chain, hasMixControls);
	addStripControls(chain);
	return chain;
}

void MixerControls::addStripControls(shared_ptr<CompoundControl> cc)
{
	canAddBusses = false;
	add(cc);
}

weak_ptr<AudioControlsChain> MixerControls::getStripControls(string name)
{
	string size = to_string(getControls().size());
	for (int i = 0; i < (int)(getControls().size()); i++) {
		auto c = getControls()[i].lock();
		if (c->getName().compare(name) == 0) {
			try {
				return dynamic_pointer_cast<AudioControlsChain>(c);
			}
			catch (const bad_cast& e) {
				string msg = e.what();
				MLOG("MixerControls.getStripControls bad cast: " + msg);
			}
		}
	}
	return {};
}

weak_ptr<AudioControlsChain> MixerControls::getStripControls(int id, int index)
{
	for (auto& c : controls) {
		if (c->getId() == id && dynamic_pointer_cast<AudioControlsChain>(c)->getInstanceIndex() == index) {
			return dynamic_pointer_cast<AudioControlsChain>(c);
		}
	}
	return {};
}

FaderControl* MixerControls::createFaderControl(bool muted)
{
    return new GainControl(muted);
}
