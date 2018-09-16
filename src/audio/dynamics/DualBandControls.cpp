#include <audio/dynamics/DualBandControls.hpp>

#include <audio/dynamics/CompressorControls.hpp>
#include <audio/dynamics/CrossoverControl.hpp>

using namespace ctoot::audio::dynamics;
using namespace std;

DualBandControls::DualBandControls()
	: MultiBandControls("Dual.Band.Compressor")
{
	add(std::move(make_shared<CompressorControls>("Low", 0)));
	add(std::move(make_shared<CrossoverControl>(0, "Mid", 1000.0f)));
	add(std::move(make_shared<CompressorControls>("High", 30)));
}
