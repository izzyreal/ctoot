#include <audio/basic/BasicServiceProvider.hpp>

#include <audio/basic/BasicIds.hpp>
#include <audio/basic/tap/TapControls.hpp>
#include <audio/basic/tap/TapProcess.hpp>
#include <audio/core/AudioControls.hpp>
#include <audio/core/AudioProcess.hpp>

#include <audio/analysis/SpectrumAnalyserControls.hpp>
#include <audio/analysis/SpectrumAnalyserProcess.hpp>

#include <audio/basic/trim/TrimControls.hpp>
#include <audio/basic/trim/TrimProcess.hpp>

using namespace ctoot::audio::basic;
using namespace std;

BasicServiceProvider::BasicServiceProvider()
	: ctoot::audio::spi::TootAudioServiceProvider("Basic", "0.1")
{
    auto family = "Basic";
	addControls("ctoot::audio::core::AudioControls", BasicIds::TRIM, "ctoot::audio::basic::trim::TrimControls", family, "0.1");
	addControls("ctoot::audio::core::AudioControls", BasicIds::TAP, "ctoot::audio::basic::tap::TapControls", family, "0.1");
	addControls("ctoot::audio::core::AudioControls", BasicIds::SPECTRUM_ANALYSER, "ctoot::audio::analysis::SpectrumAnalyserControls", family, "0.1");
}

shared_ptr<ctoot::audio::core::AudioProcess> BasicServiceProvider::createProcessor(std::weak_ptr<ctoot::audio::core::AudioControls> c)
{
	auto name = c.lock()->getName();
	if (name.compare("Tap") == 0) {
		return make_shared<tap::TapProcess>(dynamic_pointer_cast<tap::TapControls>(c.lock()).get());
	}
	else if (name.compare("Trim") == 0) {
		return make_shared<trim::TrimProcess>(dynamic_pointer_cast<trim::TrimControls>(c.lock()));
	}
	else if (name.find("SpectrumAnalyser") != string::npos) {
		return make_shared<analysis::SpectrumAnalyserProcess>(dynamic_pointer_cast<analysis::SpectrumAnalyserControls>(c.lock()));
	}
	return {};
}
