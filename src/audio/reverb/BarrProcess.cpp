#include "BarrProcess.hpp"

#include <VecUtil.hpp>

#include <Logger.hpp>

using namespace std;
using namespace ctoot::audio::reverb;

BarrProcess::BarrProcess(weak_ptr<BarrVariables> vars)
{
	this->vars = vars;
	ipd = Delay(1 + vars.lock()->getMaxPreDelaySamples());
	auto sizes = vars.lock()->getSizes();
	// input diffusion
	auto sz = sizes[4];
	id1a = Diffuser(sz[0]);
	id1b = Diffuser(sz[1]);
	id2a = Diffuser(sz[2]);
	id2b = Diffuser(sz[3]);
	// the 4 blocks form a tank for the reverb tail
	std::vector<std::vector<int>>tapsLeft = vars.lock()->getLeftTaps();
	std::vector<std::vector<int>>tapsRight = vars.lock()->getRightTaps();
	block1 = Block(sizes[0], tapsLeft[0], tapsRight[0]);
	block2 = Block(sizes[1], tapsLeft[1], tapsRight[1]);
	block3 = Block(sizes[2], tapsLeft[2], tapsRight[2]);
	block4 = Block(sizes[3], tapsLeft[3], tapsRight[3]);
}

BarrProcess::~BarrProcess() {
}

const float BarrProcess::GAIN_8 = 0.35f;


void BarrProcess::cacheVariables() {
	auto lVars = vars.lock();
	preDelaySamples = lVars->getPreDelaySamples();
	bandwidth = lVars->getBandwidth();
	inputDiffusion = lVars->getInputDiffusion();
	damping = lVars->getDamping();
	decay = lVars->getDecay();
	decayDiffusion = lVars->getDecayDiffusion();
	size = lVars->getSize();
	if (size != prevSize) {
		block1.resize(size);
		block2.resize(size);
		block3.resize(size);
		block4.resize(size);
		prevSize = size;
	}
	decay -= 0.25f*(1.f - size); // fix blowup at small sizes 
}

// could feed left into 1, right into 3 but input diffusion would need to be stereo!
void BarrProcess::reverb(float left, float right) {
	float sample = GAIN_8 * idiffuse(left + right);
	float sample2 = halfInserts ? 0.f : sample;
	auto d = decay;
	auto dd = decayDiffusion;
	zm1 = block4.tick(sample2 + damp2.filter(block3.tick(sample + block2.tick(sample2 +	damp1.filter(block1.tick(sample + zm1, d, dd),	damping), d, dd), d, dd), damping),d,dd);
}

float BarrProcess::left() {
	return block1.left() + block2.left() + block3.left() + block4.left();
}

float BarrProcess::right() {
	return block1.right() + block2.right() + block3.right() + block4.right();
}

float BarrProcess::idiffuse(float sample) {
	// pre delay
	ipd.delay(sample);
	// bandwidth, input diffusion 1 x 2, input diffusion 2 x 2
	return id2b.diffuse(id2a.diffuse(id1b.diffuse(id1a.diffuse(bw.filter(ipd.tap(preDelaySamples), 1 - bandwidth), inputDiffusion),	inputDiffusion), inputDiffusion), inputDiffusion);
}

Block::Block() {
}

Block::Block(std::vector<int> sz, std::vector<int> left, std::vector<int> right) {
	tapsLeft = left;
	tapsRight = right;
	tl = moduru::VecUtil::CopyOf(tapsLeft, 2);
	tr = moduru::VecUtil::CopyOf(tapsRight, 2);
	dif1 = Diffuser(sz[0]);
	dif2 = Diffuser(sz[1]);
	del = Delay(sz[2]);
}

float Block::tick(float sample, float decay, float decayDiffusion) {
	// diffuse, diffuse, delay, decay
	return decay * del.delay(dif2.diffuse(dif1.diffuse(sample, decayDiffusion),	decayDiffusion));
}

float Block::left() {
	return del.tap(tl[0]) + del.tap(tl[1]);
}

float Block::right() {
	return del.tap(tr[0]) + del.tap(tr[1]);
}

void Block::resize(float factor) {
	dif1.resize(factor);
	dif2.resize(factor);
	del.resize(factor);
	calcTaps(factor);
}

void Block::calcTaps(float size) {
	for (int i = 0; i < 2; i++) {
		tl[i] = (int)(tapsLeft[i] * size);
		tr[i] = (int)(tapsRight[i] * size);
	}
}
