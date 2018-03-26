#include <audio/dynamics/DynamicsServiceProvider.hpp>

#include <audio/core/AudioControls.hpp>
#include <audio/dynamics/BusCompressorControls.hpp>
#include <audio/dynamics/BusCompressor.hpp>
#include <audio/dynamics/CompressorControls.hpp>
#include <audio/dynamics/Compressor.hpp>
#include <audio/dynamics/DynamicsControls.hpp>
#include <audio/dynamics/DynamicsIds.hpp>
#include <audio/dynamics/ExpanderControls.hpp>
#include <audio/dynamics/Expander.hpp>
#include <audio/dynamics/GateControls.hpp>
#include <audio/dynamics/Gate.hpp>
#include <audio/dynamics/LimiterControls.hpp>
#include <audio/dynamics/Limiter.hpp>
#include <audio/dynamics/MidSideCompressorControls.hpp>
#include <audio/dynamics/MidSideCompressor.hpp>
#include <audio/dynamics/MidSideQuadBandControls.hpp>
#include <audio/dynamics/MidSideMultiBandCompressor.hpp>
#include <audio/dynamics/DualBandControls.hpp>
#include <audio/dynamics/QuadBandControls.hpp>
#include <audio/dynamics/MultiBandControls.hpp>
#include <audio/dynamics/MultiBandCompressor.hpp>
#include <audio/dynamics/TremoloControls.hpp>
#include <audio/dynamics/TremoloProcessVariables.hpp>
#include <audio/dynamics/TremoloProcess.hpp>
#include <audio/dynamics/VariMuCompressorControls.hpp>
#include <audio/dynamics/VariMuCompressor.hpp>

using namespace ctoot::audio::dynamics;
using namespace std;

DynamicsServiceProvider::DynamicsServiceProvider()
	: ctoot::audio::spi::TootAudioServiceProvider("Dynamics", "0.1")
{
    auto family = ServiceProvider::description;
	/*
	add(VariMuCompressor::class_(), ::uk::org::toot::misc::Localisation::getString(u"Vari.Mu.Compressor"_j), family, u"0.1"_j);
    add(BusCompressor::class_(), ::uk::org::toot::misc::Localisation::getString(u"Bus.Compressor"_j), family, u"0.1"_j);
    add(Compressor::class_(), ::uk::org::toot::misc::Localisation::getString(u"Compressor"_j), family, u"0.2"_j);
    add(Limiter::class_(), ::uk::org::toot::misc::Localisation::getString(u"Limiter"_j), family, u"0.2"_j);
    add(Gate::class_(), ::uk::org::toot::misc::Localisation::getString(u"Gate"_j), family, u"0.1"_j);
    add(MultiBandCompressor::class_(), ::uk::org::toot::misc::Localisation::getString(u"Multi.Band.Compressor"_j), family, u"0.2"_j);
    add(MidSideCompressor::class_(), ::uk::org::toot::misc::Localisation::getString(u"Mid.Side.Compressor"_j), family, u"0.1"_j);
    add(TremoloProcess::class_(), ::uk::org::toot::misc::Localisation::getString(u"Tremolo"_j), family, u"0.1"_j);
    */
	addControls("class ctoot::audio::core::AudioControls", DynamicsIds::VARI_MU_COMPRESSOR, "class ctoot::audio::dynamics::VariMuCompressorControls", family, "0.1");
	addControls("class ctoot::audio::core::AudioControls", DynamicsIds::COMPRESSOR_ID, "class ctoot::audio::dynamics::CompressorControls", family, "0.2");
	addControls("class ctoot::audio::core::AudioControls", DynamicsIds::LIMITER_ID, "class ctoot::audio::dynamics::LimiterControls", family, "0.2");
	addControls("class ctoot::audio::core::AudioControls", DynamicsIds::GATE_ID, "class ctoot::audio::dynamics::GateControls", family, "0.1");
	addControls("class ctoot::audio::core::AudioControls", DynamicsIds::MULTI_BAND_COMPRESSOR_ID, "class ctoot::audio::dynamics::DualBandControls", family, "0.2");
	addControls("class ctoot::audio::core::AudioControls", DynamicsIds::MULTI_BAND_COMPRESSOR_ID, "class ctoot::audio::dynamics::QuadBandControls", family, "0.2");
	addControls("class ctoot::audio::core::AudioControls", DynamicsIds::MID_SIDE_COMPRESSOR_ID, "class ctoot::audio::dynamics::MidSideCompressorControls", family, "0.1");
	addControls("class ctoot::audio::core::AudioControls", DynamicsIds::MID_SIDE_MULTI_BAND_COMPRESSOR_ID, "class ctoot::audio::dynamics::MidSideQuadBandControls", family, "0.1");
	addControls("class ctoot::audio::core::AudioControls", DynamicsIds::BUS_COMPRESSOR, "class ctoot::audio::dynamics::BusCompressorControls", family, "0.1");
	addControls("class ctoot::audio::core::AudioControls", DynamicsIds::TREMOLO_ID, "class ctoot::audio::dynamics::TremoloControls", family, "0.1");
}

shared_ptr<ctoot::audio::core::AudioProcess> DynamicsServiceProvider::createProcessor(weak_ptr<ctoot::audio::core::AudioControls> c)
{
	auto name = c.lock()->getName();
	MLOG("DynamicsServiceProvider name: " + name);
	if (name.compare("Tremolo") == 0) {
		return make_shared<TremoloProcess>(dynamic_pointer_cast<TremoloProcessVariables>(c.lock()).get());
	}
	if (name.compare("Bus.Comp") == 0) {
		return make_shared<BusCompressor>(dynamic_pointer_cast<BusCompressorControls>(c.lock()).get());
	}
	if (name.compare("Vari.Mu.Compressor") == 0) {
		return make_shared<VariMuCompressor>(dynamic_pointer_cast<VariMuCompressorControls>(c.lock()).get());
	}
	if (name.compare("Compressor") == 0) {
		return make_shared<Compressor>(dynamic_pointer_cast<CompressorControls>(c.lock()).get());
	}
	if (name.compare("Limiter") == 0) {
		return make_shared<Limiter>(dynamic_pointer_cast<LimiterControls>(c.lock()).get());
	}
	if (name.compare("Gate") == 0) {
		return make_shared<Gate>(dynamic_pointer_cast<GateControls>(c.lock()).get());
	}
	if (name.compare("Dual.Band.Compressor") == 0 || name.compare("Quad.Band.Compressor") == 0) {
		return make_shared<MultiBandCompressor>(dynamic_pointer_cast<MultiBandControls>(c.lock()).get());
	}
	if (name.compare("Mid-Side Compressor") == 0) {
		return make_shared<MidSideCompressor>(dynamic_pointer_cast<MidSideDynamicsProcessVariables>(c.lock()).get());
	}
	if (name.compare("Mid.Side.Quad.Band.Compressor") == 0) {
		return make_shared<MidSideMultiBandCompressor>(dynamic_pointer_cast<MultiBandControls>(c.lock()).get());
	}

	return nullptr;
}
