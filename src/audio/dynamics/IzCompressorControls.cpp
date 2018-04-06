#include <audio/dynamics/IzCompressorControls.hpp>

using namespace ctoot::audio::dynamics;
using namespace std;

IzCompressorControls::IzCompressorControls(string name, int32_t idOffset)
	: CompressorControls(name, idOffset)
{
	init();
}
