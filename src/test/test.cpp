#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>

#include "audio/core/AudioFormat.hpp"
#include "audio/core/AudioServices.hpp"

#include <Logger.hpp>

using namespace ctoot::audio::core;

TEST_CASE("AudioFormat is instantiated", "[audioformat]") {
	const auto sr1 = 44100.f;
	auto af = new AudioFormat(sr1, 16, 2, false, false);
	const auto sr2 = af->getSampleRate();
	delete af;
	REQUIRE(sr1 == sr2);
}

TEST_CASE("AudioServices are scanned", "[audioservices-scan]") {
	moduru::Logger::l.setPath("ctoot.log");
	std::string testControlName = "ctoot::audio::analysis::SpectrumAnalyserControls";
	AudioServices::scan();
	auto ac = AudioServices::getAvailableControls();
	REQUIRE(ac.find(testControlName) != std::string::npos);
	auto testControl = AudioServices::createControls(testControlName);
	REQUIRE(testControl);
	auto name = testControl->getName();
	REQUIRE(name.compare("SpectrumAnalyser") == 0);
}
