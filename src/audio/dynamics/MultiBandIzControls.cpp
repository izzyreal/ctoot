#include <audio/dynamics/MultiBandIzControls.hpp>

#include <audio/dynamics/IzBandCompressorControls.hpp>
#include <audio/dynamics/CrossoverControl.hpp>

using namespace ctoot::audio::dynamics;
using namespace std;

MultiBandIzControls::MultiBandIzControls()
	: MultiBandControls("MultiBandIzCompressor")
{
   add(make_shared<IzBandCompressorControls>("Low"));
   add(make_shared<CrossoverControl>("Low Freq", 250.0f));
   add(make_shared<IzBandCompressorControls>("Lo.Mid"));
   add(make_shared<CrossoverControl>("Mid Freq", 1000.0f));
   add(make_shared<IzBandCompressorControls>("Hi.Mid"));
   add(make_shared<CrossoverControl>("High Freq", 4000.0f));
   add(make_shared<IzBandCompressorControls>("High"));
}
