#include "ReverbServiceProvider.hpp"

#include "BarrControls.hpp"
#include "ReverbIds.hpp"

#include <memory>

using namespace std;
using namespace ctoot::audio::reverb;
using namespace ctoot::audio::spi;

ReverbServiceProvider::ReverbServiceProvider()
	: TootAudioServiceProvider("Reverb", "0.1")
{
	string family = description;
	/*
	addControls(PlateControls.class, ReverbIds.PLATE_ID, getString("Plate.Reverb"), family, "0.1");
	add(PlateProcess.class, getString("Plate.Reverb"), family, "0.1");
	*/
	addControls("class ctoot::audio::core::AudioControls", ctoot::audio::reverb::ReverbIds::BARR_ID, "class ctoot::audio::reverb::BarrControls", family, "0.1");
	//add("class ctoot::audio::reverb::BarrProcess", "Barr.Reverb", family, "0.1");
}

shared_ptr<ctoot::audio::core::AudioProcess> ReverbServiceProvider::createProcessor(weak_ptr<ctoot::audio::core::AudioControls> c) {
	if (c.lock()->getName().compare("Barr.Reverb") == 0) {
		return std::make_shared<BarrProcess>(dynamic_pointer_cast<BarrVariables>(c.lock()));
	}
	return {}; // caller then tries another provider
}
