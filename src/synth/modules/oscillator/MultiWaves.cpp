#include <synth/modules/oscillator/MultiWaves.hpp>

#include <synth/modules/oscillator/MultiWave.hpp>
#include <synth/modules/oscillator/ParabolaMultiWave.hpp>
#include <synth/modules/oscillator/SawtoothMultiWave.hpp>

#include <Logger.hpp>

using namespace ctoot::synth::modules::oscillator;
using namespace std;

int32_t MultiWaves::size = 2048;
string MultiWaves::SQUARE = "Square";
string MultiWaves::SAW = "Saw";
vector<string> MultiWaves::names = { SQUARE, SAW };
std::shared_ptr<MultiWave> MultiWaves::square;
std::shared_ptr<MultiWave> MultiWaves::saw;


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
	MLOG("Tryin get mw " + name);
	if (name.compare(SQUARE) == 0) {
		if (!square) {
			MLOG("Creating square");
			square = createSquareWave(size);
		}
		else {
			MLOG("square already created");
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
    auto res = make_shared<SawtoothMultiWave>();
	res->init(nsamples, int32_t(20000));
	auto foo = res->getWave(0).lock();
	return res;
}

shared_ptr<MultiWave> MultiWaves::createSawtoothWave(int32_t nsamples)
{
    auto res = make_shared<ParabolaMultiWave>();
	res->init(nsamples, int32_t(20000));
	return res;
}
