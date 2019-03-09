#include <audio/dynamics/izcompressor/IzCompressorControls.hpp>

using namespace ctoot::audio::dynamics::izcompressor;
using namespace std;

IzCompressorControls::IzCompressorControls(string name, int32_t idOffset)
	: CompressorControls(name, idOffset)
{
	init();
}
