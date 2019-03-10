#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "../main/audio/core/AudioFormat.hpp"
#include "../main/audio/core/AudioServices.hpp"

using namespace ctoot::audio::core;

TEST_CASE("AudioFormat is instantiated", "[audioformat]") {
	const auto sr1 = 44100.f;
	auto af = new AudioFormat(sr1, 16, 2, false, false);
	const auto sr2 = af->getSampleRate();
	delete af;
	REQUIRE(sr1 == sr2);
}

TEST_CASE("AudioServices are scanned", "[audioservices-scan]") {
	std::string testControlName = "ctoot::audio::analysis::SpectrumAnalyserControls";
	AudioServices::scan();
	auto ac = AudioServices::getAvailableControls();
	REQUIRE(ac.find(testControlName) != std::string::npos);
	auto testControl = AudioServices::createControls(testControlName);
	REQUIRE(testControl);
	auto name = testControl->getName();
	REQUIRE(name.compare("SpectrumAnalyser") == 0);
}
