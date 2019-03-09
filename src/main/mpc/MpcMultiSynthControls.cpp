#include <mpc/MpcMultiSynthControls.hpp>

using namespace ctoot::mpc;
using namespace std;

MpcMultiSynthControls::MpcMultiSynthControls()
{
}

void MpcMultiSynthControls::setSampleRate(int sampleRate) {
	this->sampleRate = sampleRate;
}

int MpcMultiSynthControls::getSampleRate() {
	return sampleRate;
}

string MpcMultiSynthControls::getName()
{
	return "MpcMultiSynth";
}

MpcMultiSynthControls::~MpcMultiSynthControls() {
}
