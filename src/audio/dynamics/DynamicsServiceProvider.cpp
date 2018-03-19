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
#include <audio/dynamics/DualBandControls.hpp>
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
    addControls(VariMuCompressorControls::class_(), DynamicsIds::VARI_MU_COMPRESSOR, ::uk::org::toot::misc::Localisation::getString(u"Vari.Mu.Compressor"_j), family, u"0.1"_j);
    addControls(BusCompressorControls::class_(), DynamicsIds::BUS_COMPRESSOR, ::uk::org::toot::misc::Localisation::getString(u"Bus.Compressor"_j), family, u"0.1"_j);
    addControls(CompressorControls::class_(), DynamicsIds::COMPRESSOR_ID, ::uk::org::toot::misc::Localisation::getString(u"Compressor"_j), family, u"0.2"_j);
    addControls(LimiterControls::class_(), DynamicsIds::LIMITER_ID, ::uk::org::toot::misc::Localisation::getString(u"Limiter"_j), family, u"0.2"_j);
    addControls(GateControls::class_(), DynamicsIds::GATE_ID, ::uk::org::toot::misc::Localisation::getString(u"Gate"_j), family, u"0.1"_j);
    addControls(DualBandControls::class_(), DynamicsIds::MULTI_BAND_COMPRESSOR_ID, ::uk::org::toot::misc::Localisation::getString(u"Dual.Band.Compressor"_j), family, u"0.2"_j);
    addControls(MidSideCompressorControls::class_(), DynamicsIds::MID_SIDE_COMPRESSOR_ID, ::uk::org::toot::misc::Localisation::getString(u"Mid.Side.Compressor"_j), family, u"0.1"_j);
    addControls(TremoloControls::class_(), DynamicsIds::TREMOLO_ID, ::uk::org::toot::misc::Localisation::getString(u"Tremolo"_j), family, u"0.1"_j);
    add(VariMuCompressor::class_(), ::uk::org::toot::misc::Localisation::getString(u"Vari.Mu.Compressor"_j), family, u"0.1"_j);
    add(BusCompressor::class_(), ::uk::org::toot::misc::Localisation::getString(u"Bus.Compressor"_j), family, u"0.1"_j);
    add(Compressor::class_(), ::uk::org::toot::misc::Localisation::getString(u"Compressor"_j), family, u"0.2"_j);
    add(Limiter::class_(), ::uk::org::toot::misc::Localisation::getString(u"Limiter"_j), family, u"0.2"_j);
    add(Gate::class_(), ::uk::org::toot::misc::Localisation::getString(u"Gate"_j), family, u"0.1"_j);
    add(MultiBandCompressor::class_(), ::uk::org::toot::misc::Localisation::getString(u"Multi.Band.Compressor"_j), family, u"0.2"_j);
    add(MidSideCompressor::class_(), ::uk::org::toot::misc::Localisation::getString(u"Mid.Side.Compressor"_j), family, u"0.1"_j);
    add(TremoloProcess::class_(), ::uk::org::toot::misc::Localisation::getString(u"Tremolo"_j), family, u"0.1"_j);
	*/
}

shared_ptr<ctoot::audio::core::AudioProcess> DynamicsServiceProvider::createProcessor(weak_ptr<ctoot::audio::core::AudioControls> c) {
{
	/*
    if(dynamic_cast< VariMuCompressorControls* >(c) != nullptr) {
        return new VariMuCompressor(java_cast< VariMuCompressorControls* >(c));
    }
    if(dynamic_cast< BusCompressorControls* >(c) != nullptr) {
        return new BusCompressor(java_cast< BusCompressorControls* >(c));
    }
    if(dynamic_cast< MidSideCompressorControls* >(c) != nullptr) {
        return new MidSideCompressor(java_cast< MidSideCompressorControls* >(c));
    }
    if(dynamic_cast< MultiBandControls* >(c) != nullptr) {
        return new MultiBandCompressor(java_cast< MultiBandControls* >(c));
    }
    if(dynamic_cast< TremoloProcess_Variables* >(c) != nullptr) {
        return new TremoloProcess(java_cast< TremoloProcess_Variables* >(c));
    }
    if(!(dynamic_cast< DynamicsControls* >(c) != nullptr))
        return nullptr;

    if(dynamic_cast< CompressorControls* >(c) != nullptr) {
        return new Compressor(java_cast< CompressorControls* >(c));
    } else if(dynamic_cast< LimiterControls* >(c) != nullptr) {
        return new Limiter(java_cast< LimiterControls* >(c));
    } else if(dynamic_cast< ExpanderControls* >(c) != nullptr) {
        return new Expander(java_cast< ExpanderControls* >(c));
    } else if(dynamic_cast< GateControls* >(c) != nullptr) {
        return new Gate(java_cast< GateControls* >(c));
    }
	*/
    return nullptr;
}
