#include <audio/dynamics/QuadBandControls.hpp>

#include <audio/dynamics/CompressorControls.hpp>
#include <audio/dynamics/CrossoverControl.hpp>

using namespace ctoot::audio::dynamics;
using namespace std;

QuadBandControls::QuadBandControls()
	: MultiBandControls("Quad.Band.Compressor")
{
   add(make_shared<CompressorControls>("Low", 0));
   add(make_shared<CrossoverControl>(0, "Low Freq", 250.0f));
   add(make_shared<CompressorControls>("Lo.Mid", 10));
   add(make_shared<CrossoverControl>(10, "Mid Freq", 1000.0f));
   add(make_shared<CompressorControls>("Hi.Mid", 20));
   add(make_shared<CrossoverControl>(20, "High Freq", 4000.0f));
   add(make_shared<CompressorControls>("High", 30));
}
