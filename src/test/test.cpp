#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>

#include "audio/core/AudioFormat.hpp"

using namespace ctoot::audio::core;

TEST_CASE("AudioFormat is instantiated", "[audioformat]") {
	const auto sr1 = 44100.f;
	auto af = new AudioFormat(sr1, 16, 2, false, false);
	const auto sr2 = af->getSampleRate();
	delete af;
	REQUIRE(sr1 == sr2);
}
