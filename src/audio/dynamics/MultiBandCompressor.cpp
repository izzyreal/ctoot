// Generated from /toot2/src/uk/org/toot/audio/dynamics/MultiBandCompressor.java
#include <audio/dynamics/MultiBandCompressor.hpp>

#include <java/lang/ArrayStoreException.hpp>
#include <java/lang/ClassCastException.hpp>
#include <java/lang/NullPointerException.hpp>
#include <java/lang/Object.hpp>
#include <java/lang/String.hpp>
#include <java/lang/StringBuilder.hpp>
#include <java/util/List.hpp>
#include <org/tritonus/share/sampled/FloatSampleBuffer.hpp>
#include <audio/core/AudioBuffer.hpp>
#include <audio/core/AudioProcess.hpp>
#include <audio/core/FloatDenormals.hpp>
#include <audio/core/SimpleAudioProcess.hpp>
#include <audio/dynamics/CompressorControls.hpp>
#include <audio/dynamics/Compressor.hpp>
#include <audio/dynamics/CrossoverControl.hpp>
#include <audio/dynamics/CrossoverSection.hpp>
#include <audio/dynamics/DynamicsProcess.hpp>
#include <audio/dynamics/MultiBandControls.hpp>
#include <audio/filter/Crossover.hpp>
#include <audio/filter/IIRCrossover.hpp>
#include <control/Control.hpp>
#include <dsp/filter/FilterShape.hpp>
#include <Array.hpp>
#include <ObjectArray.hpp>
#include <SubArray.hpp>

template<typename ComponentType, typename... Bases> struct SubArray;
namespace org
{
    namespace tritonus
    {
        namespace share
        {
            namespace sampled
            {
typedef ::SubArray< ::org::tritonus::share::sampled::FloatSampleBuffer, ::java::lang::ObjectArray > FloatSampleBufferArray;
            } // sampled
        } // share
    } // tritonus
} // org

namespace uk
{
    namespace org
    {
        namespace toot
        {
            namespace audio
            {
                namespace core
                {
typedef ::SubArray< ctoot::audio::core::AudioBuffer, ::org::tritonus::share::sampled::FloatSampleBufferArray > AudioBufferArray;
typedef ::SubArray< ctoot::audio::core::AudioProcess, ::java::lang::ObjectArray > AudioProcessArray;
typedef ::SubArray< ctoot::audio::core::SimpleAudioProcess, ::java::lang::ObjectArray, AudioProcessArray > SimpleAudioProcessArray;
                } // core

                namespace dynamics
                {
typedef ::SubArray< ctoot::audio::dynamics::DynamicsProcess, ctoot::audio::core::SimpleAudioProcessArray > DynamicsProcessArray;
typedef ::SubArray< ctoot::audio::dynamics::Compressor, DynamicsProcessArray > CompressorArray;
                } // dynamics
            } // audio
        } // toot
    } // org
} // uk

template<typename T, typename U>
static T java_cast(U* u)
{
    if(!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    if(!t) throw new ::java::lang::ClassCastException();
    return t;
}

template<typename T>
static T* npc(T* t)
{
    if(!t) throw new ::java::lang::NullPointerException();
    return t;
}

uk::org::toot::audio::dynamics::MultiBandCompressor::MultiBandCompressor(const ::default_init_tag&)
    : super(*static_cast< ::default_init_tag* >(0))
{
    clinit();
}

uk::org::toot::audio::dynamics::MultiBandCompressor::MultiBandCompressor(MultiBandControls* c) 
    : MultiBandCompressor(*static_cast< ::default_init_tag* >(0))
{
    ctor(c);
}

void MultiBandCompressor::init()
{
    nchans = -int32_t(1);
    nsamples = -int32_t(1);
    sampleRate = -int32_t(1);
}

void MultiBandCompressor::ctor(MultiBandControls* c)
{
    super::ctor();
    init();
    multiBandControls = c;
    wasBypassed = !npc(c)->isBypassed();
    auto controls = npc(c)->getControls();
    nbands = (npc(controls)->size() + int32_t(1)) / int32_t(2);
    if(nbands > 2) {
        nbands = 4;
        loXO = createCrossover(java_cast< CrossoverControl* >(java_cast< ctoot::control::Control* >(npc(controls)->get(int32_t(1) + int32_t(1)))));
        midXO = createCrossover(java_cast< CrossoverControl* >(java_cast< ctoot::control::Control* >(npc(controls)->get(int32_t(3) + int32_t(1)))));
        hiXO = createCrossover(java_cast< CrossoverControl* >(java_cast< ctoot::control::Control* >(npc(controls)->get(int32_t(5) + int32_t(1)))));
    } else {
        midXO = createCrossover(java_cast< CrossoverControl* >(java_cast< ctoot::control::Control* >(npc(controls)->get(int32_t(1) + int32_t(1)))));
        nbands = 2;
    }
    compressors = new CompressorArray(nbands);
    for (auto i = int32_t(0); i < nbands; i++) {
        compressors->set(i, new Compressor(java_cast< CompressorControls* >(java_cast< ctoot::control::Control* >(npc(controls)->get(int32_t(1) + i * int32_t(2))))));
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
    npc(midXO)->clear();
    if(nbands > 2) {
        npc(loXO)->clear();
        npc(hiXO)->clear();
    }
    for (auto b = int32_t(0); b < nbands; b++) {
        npc((*compressors)[b])->clear();
    }
}

int32_t uk::org::toot::audio::dynamics::MultiBandCompressor::processAudio(ctoot::audio::core::AudioBuffer* buffer)
{
    auto bypassed = npc(multiBandControls)->isBypassed();
    if(bypassed) {
        if(!wasBypassed) {
            clear();
            wasBypassed = true;
        }
        return AUDIO_OK;
    }
    conformBandBuffers(buffer);
    split(midXO, buffer, (*bandBuffers)[int32_t(0)], (*bandBuffers)[int32_t(1)]);
    if(nbands > 2) {
        split(hiXO, (*bandBuffers)[int32_t(1)], (*bandBuffers)[int32_t(2)], (*bandBuffers)[int32_t(3)]);
        split(loXO, (*bandBuffers)[int32_t(0)], (*bandBuffers)[int32_t(0)], (*bandBuffers)[int32_t(1)]);
    }
    for (auto b = int32_t(0); b < nbands; b++) {
        npc((*compressors)[b])->processAudio((*bandBuffers)[b]);
    }
    buffer->makeSilence();
    auto nc = buffer->getChannelCount();
    auto ns = buffer->getSampleCount();
    float out;
    for (auto c = int32_t(0); c < nc; c++) {
        auto samples = buffer->getChannel(c);
        for (auto b = int32_t(0); b < nbands; b++) {
            auto bandsamples = npc((*bandBuffers)[b])->getChannel(c);
            for (auto i = int32_t(0); i < ns; i++) {
                out = (*bandsamples)[i];
                if(ctoot::audio::core::FloatDenormals::isDenormalOrZero(out))
                    continue;

                (*samples)[i] += ((b & int32_t(1)) == 1) ? -out : out;
            }
        }
    }
    wasBypassed = bypassed;
    return AUDIO_OK;
}

void MultiBandCompressor::conformBandBuffers(ctoot::audio::core::AudioBuffer* buf)
{
    auto nc = npc(buf)->getChannelCount();
    auto ns = npc(buf)->getSampleCount();
    auto sr = static_cast< int32_t >(npc(buf)->getSampleRate());
    if(bandBuffers == nullptr) {
        bandBuffers = new ctoot::audio::core::AudioBufferArray(nbands);
        for (auto b = int32_t(0); b < nbands; b++) {
            bandBuffers->set(b, new ctoot::audio::core::AudioBuffer(::java::lang::StringBuilder().append(u"MultiBandCompressor band "_j)->append((int32_t(1) + b))->toString(), nc, ns, sr));
        }
        updateSampleRate(sr);
    } else {
        if(nchans >= nc && nsamples == ns && sampleRate == sr)
            return;

        for (auto b = int32_t(0); b < nbands; b++) {
            auto bbuf = (*bandBuffers)[b];
            if(nchans < nc) {
                for (auto i = int32_t(0); i < nc - nchans; i++) {
                    npc(bbuf)->addChannel(true);
                }
            }
            if(nsamples != ns) {
                npc(bbuf)->changeSampleCount(ns, false);
            }
            if(sampleRate != sr) {
                npc(bbuf)->setSampleRate(sr);
                updateSampleRate(sr);
            }
        }
    }
    nchans = nc;
    nsamples = ns;
    sampleRate = sr;
}

void MultiBandCompressor::split(ctoot::audio::filter::Crossover* xo, ctoot::audio::core::AudioBuffer* source, ctoot::audio::core::AudioBuffer* low, ctoot::audio::core::AudioBuffer* high)
{
    for (auto c = int32_t(0); c < npc(source)->getChannelCount(); c++) {
        npc(xo)->filter(npc(source)->getChannel(c), npc(low)->getChannel(c), npc(high)->getChannel(c), npc(source)->getSampleCount(), c);
    }
}

uk::org::toot::audio::filter::Crossover* uk::org::toot::audio::dynamics::MultiBandCompressor::createCrossover(CrossoverControl* c)
{
    return new ctoot::audio::filter::IIRCrossover(new CrossoverSection(c, ::uk::org::toot::dsp::filter::FilterShape::LPF), new CrossoverSection(c, ::uk::org::toot::dsp::filter::FilterShape::HPF));
}

void MultiBandCompressor::updateSampleRate(int32_t rate)
{
    npc(midXO)->setSampleRate(rate);
    if(nbands > 2) {
        npc(loXO)->setSampleRate(rate);
        npc(hiXO)->setSampleRate(rate);
    }
}

extern java::lang::Class *class_(const char16_t *c, int n);

java::lang::Class* uk::org::toot::audio::dynamics::MultiBandCompressor::class_()
{
    static ::java::lang::Class* c = ::class_(u"uk.org.toot.audio.dynamics.MultiBandCompressor", 46);
    return c;
}

java::lang::Class* uk::org::toot::audio::dynamics::MultiBandCompressor::getClass0()
{
    return class_();
}

