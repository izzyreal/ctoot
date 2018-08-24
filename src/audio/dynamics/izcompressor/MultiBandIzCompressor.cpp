#include <audio/dynamics/izcompressor/MultiBandIzCompressor.hpp>

#include <audio/dynamics/izcompressor/IzBandCompressorControls.hpp>
#include <audio/dynamics/izcompressor/IzCompressor.hpp>

#include <audio/core/AudioBuffer.hpp>
#include <audio/core/AudioProcess.hpp>
#include <audio/core/FloatDenormals.hpp>
#include <audio/core/SimpleAudioProcess.hpp>
#include <audio/dynamics/CrossoverControl.hpp>
#include <audio/dynamics/CrossoverSection.hpp>
#include <audio/dynamics/DynamicsProcess.hpp>
#include <audio/dynamics/izcompressor/MultiBandIzControls.hpp>
#include <audio/filter/Crossover.hpp>
#include <audio/filter/IIRCrossover.hpp>
#include <control/Control.hpp>
#include <dsp/filter/FilterShape.hpp>

using namespace ctoot::audio::dynamics::izcompressor;
using namespace ctoot::audio::dynamics;
using namespace std;

MultiBandIzCompressor::MultiBandIzCompressor(MultiBandIzControls* c)
{
	multiBandControls = c;
	wasBypassed = !c->isBypassed();
	auto controls = c->getControls();
	nbands = (controls.size() + 1) / 2;
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
	compressors = vector<IzCompressor*>(nbands);
	for (auto i = 0; i < nbands; i++) {
		compressors[i] = new IzCompressor(dynamic_cast<IzBandCompressorControls*>(controls[1 + (i * 2)].lock().get()));
	}
}

void MultiBandIzCompressor::open()
{
}

void MultiBandIzCompressor::close()
{
}

void MultiBandIzCompressor::clear()
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

int32_t MultiBandIzCompressor::processAudio(ctoot::audio::core::AudioBuffer* buffer)
{
	auto bypassed = multiBandControls->isBypassed();
	if (bypassed) {
		if (!wasBypassed) {
			clear();
			wasBypassed = true;
		}
		return AUDIO_OK;
	}
	
	const float inputGain = multiBandControls->getInputGain();
	smoothedInputGain += 0.05f * (inputGain - smoothedInputGain);

	auto l = buffer->getChannel(0);
	auto r = buffer->getChannel(1);
	for (int i = 0; i < buffer->getSampleCount(); i++) {
		(*l)[i] *= smoothedInputGain;
		(*r)[i] *= smoothedInputGain;
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
		auto samples = buffer->getChannel(c);
		for (auto b = 0; b < nbands; b++) {
			auto bandsamples = bandBuffers[b]->getChannel(c);
			for (auto i = 0; i < ns; i++) {
				out = (*bandsamples)[i];
				if (ctoot::audio::core::FloatDenormals::isDenormalOrZero(out))
					continue;

				(*samples)[i] += ((b & 1) == 1) ? -out : out;
			}
		}
	}
	wasBypassed = bypassed;
	return AUDIO_OK;
}

void MultiBandIzCompressor::conformBandBuffers(ctoot::audio::core::AudioBuffer* buf)
{
	auto nc = buf->getChannelCount();
	auto ns = buf->getSampleCount();
	auto sr = static_cast<int32_t>(buf->getSampleRate());
	if (bandBuffers.size() == 0) {
		bandBuffers = vector<ctoot::audio::core::AudioBuffer*>(nbands);
		for (auto b = 0; b < nbands; b++) {
			bandBuffers[b] = new ctoot::audio::core::AudioBuffer("MultiBandIzCompressor band " + to_string(1 + b), nc, ns, sr);
		}
		updateSampleRate(sr);
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
				updateSampleRate(sr);
			}
		}
	}
	nchans = nc;
	nsamples = ns;
	sampleRate = sr;
}

void MultiBandIzCompressor::split(ctoot::audio::filter::Crossover* xo, ctoot::audio::core::AudioBuffer* source, ctoot::audio::core::AudioBuffer* low, ctoot::audio::core::AudioBuffer* high)
{
    for (auto c = 0; c < source->getChannelCount(); c++) {
        xo->filter(source->getChannel(c), low->getChannel(c), high->getChannel(c), source->getSampleCount(), c);
    }
}

ctoot::audio::filter::Crossover* MultiBandIzCompressor::createCrossover(CrossoverControl* c)
{
	auto cs1 = new CrossoverSection(c, ctoot::dsp::filter::FilterShape::LPF);
	auto cs2 = new CrossoverSection(c, ctoot::dsp::filter::FilterShape::HPF);
	return new ctoot::audio::filter::IIRCrossover(cs1, cs2);
}

void MultiBandIzCompressor::updateSampleRate(int32_t rate)
{
    midXO->setSampleRate(rate);
    if(nbands > 2) {
		loXO->setSampleRate(rate);
        hiXO->setSampleRate(rate);
    }
}

MultiBandIzCompressor::~MultiBandIzCompressor() {
	for (auto& b : bandBuffers) {
		if (b != nullptr) delete b;
	}
}
