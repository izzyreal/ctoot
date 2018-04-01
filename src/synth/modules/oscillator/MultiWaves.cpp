#include <synth/modules/oscillator/MultiWaves.hpp>

#include <synth/modules/oscillator/MultiWave.hpp>
#include <synth/modules/oscillator/ParabolaMultiWave.hpp>
#include <synth/modules/oscillator/SawtoothMultiWave.hpp>

using namespace ctoot::synth::modules::oscillator;
using namespace std;

int32_t MultiWaves::size = 2048;
string MultiWaves::SQUARE = "Square";
string MultiWaves::SAW = "Saw";
vector<string> MultiWaves::names = { SQUARE, SAW };

vector<string> MultiWaves::getNames()
{
	return names;
}

void MultiWaves::init()
{
    square = createSquareWave(size);
    saw = createSawtoothWave(size);
}

weak_ptr<MultiWave> MultiWaves::get(string name)
{
	if (name.compare(SQUARE) == 0) {
		if (!square) {
			square = createSquareWave(size);
		}
		return square;
	}
	else if (name.compare(SAW) == 0) {
		if (!saw) {
			saw = createSawtoothWave(size);
		}
		return saw;
	}
	return {};
}

void MultiWaves::setSize(int32_t aSize)
{
	size = aSize;
}

shared_ptr<MultiWave> MultiWaves::createSquareWave(int32_t nsamples)
{
    return make_shared<SawtoothMultiWave>(nsamples, int32_t(20000));
}

shared_ptr<MultiWave> MultiWaves::createSawtoothWave(int32_t nsamples)
{
    return make_shared<ParabolaMultiWave>(nsamples, int32_t(20000));
}
