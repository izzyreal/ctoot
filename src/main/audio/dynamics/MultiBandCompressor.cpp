#include <audio/dynamics/MultiBandCompressor.hpp>

#include <audio/core/AudioBuffer.hpp>
#include <audio/core/AudioProcess.hpp>
#include <audio/core/FloatDenormals.hpp>
#include <audio/dynamics/CompressorControls.hpp>
#include <audio/dynamics/Compressor.hpp>
#include <audio/dynamics/CrossoverControl.hpp>
#include <audio/dynamics/CrossoverSection.hpp>
#include <audio/dynamics/MultiBandControls.hpp>
#include <audio/filter/Crossover.hpp>
#include <audio/filter/IIRCrossover.hpp>
#include <dsp/filter/FilterShape.hpp>

using namespace ctoot::audio::dynamics;
using namespace std;

MultiBandCompressor::MultiBandCompressor(MultiBandControls* c)
{
	multiBandControls = c;
	wasBypassed = !c->isBypassed();
	auto controls = c->getControls();
	nbands = (static_cast<int>(controls.size()) + 1) / 2;
	if (nbands > 2) {
		nbands = 4;
		loXO = createCrossover(dynamic_cast<CrossoverControl*>(controls[1 + 1].lock().get()));
		midXO = createCrossover(dynamic_cast<CrossoverControl*>(controls[3 + 1].lock().get()));
		hiXO = createCrossover(dynamic_cast<CrossoverControl*>(controls[5 + 1].lock().get()));
	}
	else {
		auto cc = controls[1 + 1].lock().get();
		midXO = createCrossover(dynamic_cast<CrossoverControl*>(cc));
		nbands = 2;
	}
	compressors = vector<Compressor*>(nbands);
	for (auto i = 0; i < nbands; i++) {
		compressors[i] = new Compressor(dynamic_cast<CompressorControls*>(controls[1 + (i * 2)].lock().get()));
	}

}

void MultiBandCompressor::open()
{
}

void MultiBandCompressor::close()
{
}

void MultiBandCompressor::clear()
{
	midXO->clear();
	if (nbands > 2) {
		loXO->clear();
		hiXO->clear();
	}
	for (auto b = 0; b < nbands; b++) {
		compressors[b]->clear();
	}
}

int32_t MultiBandCompressor::processAudio(ctoot::audio::core::AudioBuffer* buffer)
{
	auto bypassed = multiBandControls->isBypassed();
	if (bypassed) {
		if (!wasBypassed) {
			clear();
			wasBypassed = true;
		}
		return AUDIO_OK;
	}
	conformBandBuffers(buffer);
	split(midXO, buffer, bandBuffers[0], bandBuffers[1]);
	if (nbands > 2) {
		split(hiXO, bandBuffers[1], bandBuffers[2], bandBuffers[3]);
		split(loXO, bandBuffers[0], bandBuffers[0], bandBuffers[1]);
	}
	for (auto b = 0; b < nbands; b++) {
		compressors[b]->processAudio(bandBuffers[b]);
	}
	buffer->makeSilence();
	auto nc = buffer->getChannelCount();
	auto ns = buffer->getSampleCount();
	float out;
	for (auto c = 0; c < nc; c++) {
		auto& samples = buffer->getChannel(c);
		for (auto b = 0; b < nbands; b++) {
			auto& bandsamples = bandBuffers[b]->getChannel(c);
			for (auto i = 0; i < ns; i++) {
				out = bandsamples[i];
				if (ctoot::audio::core::FloatDenormals::isDenormalOrZero(out))
					continue;

				samples[i] += ((b & 1) == 1) ? -out : out;
			}
		}
	}
	wasBypassed = bypassed;
	return AUDIO_OK;
}

void MultiBandCompressor::conformBandBuffers(ctoot::audio::core::AudioBuffer* buf)
{
	auto nc = buf->getChannelCount();
	auto ns = buf->getSampleCount();
	auto sr = static_cast<float>(buf->getSampleRate());
	if (bandBuffers.size() == 0) {
		bandBuffers = vector<ctoot::audio::core::AudioBuffer*>(nbands);
		for (auto b = 0; b < nbands; b++) {
			bandBuffers[b] = new ctoot::audio::core::AudioBuffer("MultiBandCompressor band " + to_string(1 + b), nc, ns, sr);
		}
		updateSampleRate(static_cast<int32_t>(sr));
	}
	else {
		if (nchans >= nc && nsamples == ns && sampleRate == sr)
			return;

		for (auto b = 0; b < nbands; b++) {
			auto bbuf = bandBuffers[b];
			if (nchans < nc) {
				for (auto i = 0; i < nc - nchans; i++) {
					bbuf->addChannel(true);
				}
			}
			if (nsamples != ns) {
				bbuf->changeSampleCount(ns, false);
			}
			if (sampleRate != sr) {
				bbuf->setSampleRate(sr);
				updateSampleRate(static_cast<int32_t>(sr));
			}
		}
	}
	nchans = nc;
	nsamples = ns;
	sampleRate = static_cast<int32_t>(sr);
}

void MultiBandCompressor::split(ctoot::audio::filter::Crossover* xo, ctoot::audio::core::AudioBuffer* source, ctoot::audio::core::AudioBuffer* low, ctoot::audio::core::AudioBuffer* high)
{
    for (auto c = 0; c < source->getChannelCount(); c++) {
        xo->filter(source->getChannel(c), low->getChannel(c), high->getChannel(c), source->getSampleCount(), c);
    }
}

ctoot::audio::filter::Crossover* MultiBandCompressor::createCrossover(CrossoverControl* c)
{
	auto cs2 = new CrossoverSection(c, ctoot::dsp::filter::FilterShape::LPF);
	auto cs1 = new CrossoverSection(c, ctoot::dsp::filter::FilterShape::HPF);
	return new ctoot::audio::filter::IIRCrossover(cs1, cs2);
}

void MultiBandCompressor::updateSampleRate(int32_t rate)
{
    midXO->setSampleRate(rate);
    if(nbands > 2) {
		loXO->setSampleRate(rate);
        hiXO->setSampleRate(rate);
    }
}
