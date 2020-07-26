#include "TrimControls.hpp"

#include "TrimControl.hpp"

#include <audio/basic/BasicIds.hpp>

using namespace ctoot::audio::basic::trim;
using namespace std;

TrimControls::TrimControls()
	: AudioControls(BasicIds::TRIM, "Trim")
{
	auto trimControl = make_shared<TrimControl>(0, "Trim", TRIM_LAW(), 0.01f, 0.f, &trim);
	add(move(trimControl));
}

float TrimControls::getTrim()
{
	return trim;
}
