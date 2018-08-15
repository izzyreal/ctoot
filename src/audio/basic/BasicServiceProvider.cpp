#include <audio/basic/BasicServiceProvider.hpp>

#include <audio/basic/BasicIds.hpp>
//#include <audio/basic/stereoImage/StereoImageControls.hpp>
//#include <audio/basic/stereoImage/StereoImageProcess.hpp>
//#include <audio/basic/stereoImage/StereoImageProcessVariables.hpp>
#include <audio/basic/tap/TapControls.hpp>
#include <audio/basic/tap/TapProcess.hpp>
//#include <audio/basic/trim/TrimControls.hpp>
//#include <audio/basic/trim/TrimProcess.hpp>
#include <audio/core/AudioControls.hpp>
#include <audio/core/ChannelFormat.hpp>
#include <audio/core/AudioProcess.hpp>

#include <audio/analysis/SpectrumAnalyserControls.hpp>
#include <audio/analysis/SpectrumAnalyserProcess.hpp>

using namespace ctoot::audio::basic;
using namespace std;

BasicServiceProvider::BasicServiceProvider()
	: ctoot::audio::spi::TootAudioServiceProvider("Basic", "0.1")
{
    auto family = "Basic";
    /*
	addControls(::tap::TapControls::class_(), BasicIds::TAP, ctoot::misc::Localisation::getString("Tap"), family, u"0.1");
    addControls(::trim::TrimControls::class_(), BasicIds::TRIM, ctoot::misc::Localisation::getString("Trim"), family, u"0.1");
    addControls(::stereoImage::StereoImageControls::class_(), BasicIds::STEREO_IMAGE, ctoot::misc::Localisation::getString("Stereo.Image"), family, u"0.1", ctoot::audio::core::ChannelFormat::STEREO(), nullptr);
    add(::tap::TapProcess::class_(), ctoot::misc::Localisation::getString("Tap"), family, u"0.1");
    add(::trim::TrimProcess::class_(), ctoot::misc::Localisation::getString("Trim"), family, u"0.1");
    add(::stereoImage::StereoImageProcess::class_(), ctoot::misc::Localisation::getString("Stereo.Image"), family, u"0.1");
	*/
	addControls("class ctoot::audio::core::AudioControls", BasicIds::TAP, "class ctoot::audio::basic::tap::TapControls", family, "0.1");
	addControls("class ctoot::audio::core::AudioControls", BasicIds::SPECTRUM_ANALYSER, "class ctoot::audio::analysis::SpectrumAnalyserControls", family, "0.1");

}

shared_ptr<ctoot::audio::core::AudioProcess> BasicServiceProvider::createProcessor(std::weak_ptr<ctoot::audio::core::AudioControls> c)
{
	auto name = c.lock()->getName();
	if (name.compare("Tap") == 0) {
		return make_shared<tap::TapProcess>(dynamic_pointer_cast<tap::TapControls>(c.lock()).get());
	}
	else if (name.compare("SpectrumAnalyser") == 0) {
		return make_shared<analysis::SpectrumAnalyserProcess>(dynamic_pointer_cast<analysis::SpectrumAnalyserControls>(c.lock()));
	}
	/*
	if(dynamic_cast< ::tap::TapControls* >(c) != nullptr) {
		return new ::tap::TapProcess(java_cast< ::tap::TapControls* >(c));
	} else if(dynamic_cast< ::trim::TrimControls* >(c) != nullptr) {
		return new ::trim::TrimProcess(java_cast< ::trim::TrimControls* >(c));
	} else if(dynamic_cast< ::stereoImage::StereoImageProcessVariables* >(c) != nullptr) {
		return new ::stereoImage::StereoImageProcess(java_cast< ::stereoImage::StereoImageProcessVariables* >(c));
	}
	*/
	return {};
}
