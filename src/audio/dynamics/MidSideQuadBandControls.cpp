#include <audio/dynamics/MidSideQuadBandControls.hpp>

#include <audio/dynamics/MidSideCompressorControls.hpp>
#include <audio/dynamics/CrossoverControl.hpp>

using namespace ctoot::audio::dynamics;
using namespace std;

MidSideQuadBandControls::MidSideQuadBandControls()
	: MultiBandControls("Mid.Side.Quad.Band.Compressor")
{
   add(make_shared<MidSideCompressorControls>("Low"));
   add(make_shared<CrossoverControl>("Low Freq", 250.0f));
   add(make_shared<MidSideCompressorControls>("Lo.Mid"));
   add(make_shared<CrossoverControl>("Mid Freq", 1000.0f));
   add(make_shared<MidSideCompressorControls>("Hi.Mid"));
   add(make_shared<CrossoverControl>("High Freq", 4000.0f));
   add(make_shared<MidSideCompressorControls>("High"));
}
