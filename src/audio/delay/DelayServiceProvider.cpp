#include <audio/delay/DelayServiceProvider.hpp>

#include <audio/core/AudioControls.hpp>
#include <audio/core/ChannelFormat.hpp>
#include <audio/delay/CabMicingControls.hpp>
#include <audio/delay/CabMicingProcess_Variables.hpp>
#include <audio/delay/CabMicingProcess.hpp>
#include <audio/delay/DelayIds.hpp>
#include <audio/delay/ModulatedDelayControls.hpp>
#include <audio/delay/ModulatedDelayProcessVariables.hpp>
#include <audio/delay/ModulatedDelayProcess.hpp>
#include <audio/delay/MultiTapDelayProcessVariables.hpp>
#include <audio/delay/MultiTapDelayProcess.hpp>
#include <audio/delay/MultiTapDelayStereoControls.hpp>
#include <audio/delay/PhaserControls.hpp>
#include <audio/delay/PhaserProcess.hpp>
#include <audio/delay/TempoDelayControls.hpp>
#include <audio/delay/TempoDelayProcess.hpp>
#include <audio/delay/WowFlutterControls.hpp>
#include <audio/delay/WowFlutterProcessVariables.hpp>
#include <audio/delay/WowFlutterProcess.hpp>

using namespace ctoot::audio::delay;
using namespace ctoot::audio::core;
using namespace ctoot::control;
using namespace std;

DelayServiceProvider::DelayServiceProvider()
	: TootAudioServiceProvider("Delay", "0.2")
{
    auto family = description;
	//"Modulated.Delay"
	addControls("class ctoot::audio::core::AudioControls", DelayIds::MODULATED_DELAY_ID, "class ctoot::audio::delay::ModulatedDelayControls", family, "0.2");

	//"Stereo.Multi.Tap.Delay"
    addControls("class ctoot::audio::core::AudioControls", DelayIds::MULTI_TAP_DELAY_ID, "class ctoot::audio::delay::MultiTapDelayStereoControls", family, "0.1", ChannelFormat::STEREO(), "");
    
	//"BPM.Delay"
	addControls("class ctoot::audio::core::AudioControls", DelayIds::TEMPO_DELAY_ID, "class ctoot::audio::delay::TempoDelayControls", family, "0.2");
    
	//"Phaser"
	addControls("class ctoot::audio::core::AudioControls", DelayIds::PHASER_ID, "class ctoot::audio::delay::PhaserControls", family, "0.1", ChannelFormat::MONO(), "");
    
	//"Wow & Flutter"
	addControls("class ctoot::audio::core::AudioControls", DelayIds::WOW_FLUTTER_ID, "class ctoot::audio::delay::WowFlutterControls", family, "0.1");
    
	//"Cab.Mic"
	addControls("class ctoot::audio::core::AudioControls", DelayIds::CAB_MICING_ID, "class ctoot::audio::delay::CabMicingControls", "EQ", "0.1");
	
	/*
	add(ModulatedDelayProcess::class_(), "Modulated.Delay", family, "0.2");
    add(MultiTapDelayProcess::class_(), "Multi.Tap.Delay", family, "0.1");
    add(TempoDelayProcess::class_(), "BPM.Delay", family, "0.2");
    add(PhaserProcess::class_(), "Phaser", family, "0.1");
    add(WowFlutterProcess::class_(), "Wow & Flutter", family, "0.1");
    add(CabMicingProcess::class_(), "Cab.Mic", "EQ", "0.1");
	*/
}

shared_ptr<ctoot::audio::core::AudioProcess> DelayServiceProvider::createProcessor(weak_ptr<AudioControls> c)
{
	auto name = c.lock()->getName();
	MLOG("DelayServiceProvider::createProcessor c name: " + name);
	if (name.compare("Phaser") == 0) {
		return make_shared<PhaserProcess>(dynamic_pointer_cast<PhaserProcessVariables>(c.lock()).get());
	}
	else if (name.compare("Modulated.Delay") == 0) {
		return make_shared<ModulatedDelayProcess>(dynamic_pointer_cast<ModulatedDelayProcessVariables>(c.lock()).get());
	}
	else if (name.compare("Stereo.Multi.Tap.Delay") == 0) {
		return make_shared<MultiTapDelayProcess>(dynamic_pointer_cast<MultiTapDelayProcessVariables>(c.lock()).get());
	}
	else if (name.compare("BPM.Delay") == 0) {
		return make_shared<TempoDelayProcess>(dynamic_pointer_cast<TempoDelayProcessVariables>(c.lock()).get());
	}
	else if (name.compare("Wow") == 0) {
		return make_shared<WowFlutterProcess>(dynamic_pointer_cast<WowFlutterProcessVariables>(c.lock()).get());
	}
	else if (name.compare("Cab.Mic") == 0) {
		return make_shared<CabMicingProcess>(dynamic_pointer_cast<CabMicingProcess_Variables>(c.lock()).get());
	}
	/*
    if(dynamic_cast< ModulatedDelayProcessVariables* >(c) != nullptr) {
        return new ModulatedDelayProcess(java_cast< ModulatedDelayProcessVariables* >(c));
    } else if(dynamic_cast< MultiTapDelayProcessVariables* >(c) != nullptr) {
        return new MultiTapDelayProcess(java_cast< MultiTapDelayProcessVariables* >(c));
    } else if(dynamic_cast< TempoDelayControls* >(c) != nullptr) {
        return new TempoDelayProcess(java_cast< TempoDelayControls* >(c));
    } else if(dynamic_cast< PhaserControls* >(c) != nullptr) {
        return new PhaserProcess(java_cast< PhaserControls* >(c));
    } else if(dynamic_cast< CabMicingProcess_Variables* >(c) != nullptr) {
        return new CabMicingProcess(java_cast< CabMicingProcess_Variables* >(c));
    } else if(dynamic_cast< WowFlutterProcessVariables* >(c) != nullptr) {
        return new WowFlutterProcess(java_cast< WowFlutterProcessVariables* >(c));
    }
	*/
	return {};
}

std::shared_ptr<ctoot::audio::core::AudioControls> DelayServiceProvider::createControls(int moduleId)
{
	if (moduleId == DelayIds::STEREO_MODULATED_DELAY_ID) {
		return TootAudioServiceProvider::createControls(DelayIds::MODULATED_DELAY_ID);
	}
	return TootAudioServiceProvider::createControls(moduleId);
}
