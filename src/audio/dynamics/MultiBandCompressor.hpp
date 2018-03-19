// Generated from /toot2/src/uk/org/toot/audio/dynamics/MultiBandCompressor.java

#pragma once

#include <fwd-toot2.hpp>
#include <java/lang/fwd-toot2.hpp>
#include <org/tritonus/share/sampled/fwd-toot2.hpp>
#include <audio/core/fwd-toot2.hpp>
#include <audio/dynamics/fwd-toot2.hpp>
#include <audio/filter/fwd-toot2.hpp>
#include <java/lang/Object.hpp>
#include <audio/core/AudioProcess.hpp>

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

struct default_init_tag;

class MultiBandCompressor
    : public virtual ::java::lang::Object
    , public virtual ctoot::audio::core::AudioProcess
{

public:
    typedef ::java::lang::Object super;

private:
    MultiBandControls* multiBandControls {  };
    CompressorArray* compressors {  };
    ctoot::audio::filter::Crossover* midXO {  };
    ctoot::audio::filter::Crossover* hiXO {  };
    ctoot::audio::filter::Crossover* loXO {  };
    ctoot::audio::core::AudioBufferArray* bandBuffers {  };
    int32_t nbands {  };
    int32_t nchans {  };
    int32_t nsamples {  };
    int32_t sampleRate {  };
    bool wasBypassed {  };
protected:
    void ctor(MultiBandControls* c);

public:
    void open() override;
    void close() override;
    virtual void clear();
    int32_t processAudio(ctoot::audio::core::AudioBuffer* buffer) override;

public: /* protected */
    virtual void conformBandBuffers(ctoot::audio::core::AudioBuffer* buf);
    virtual void split(ctoot::audio::filter::Crossover* xo, ctoot::audio::core::AudioBuffer* source, ctoot::audio::core::AudioBuffer* low, ctoot::audio::core::AudioBuffer* high);
    virtual ctoot::audio::filter::Crossover* createCrossover(CrossoverControl* c);
    virtual void updateSampleRate(int32_t rate);

    // Generated

public:
    MultiBandCompressor(MultiBandControls* c);
protected:
    MultiBandCompressor(const ::default_init_tag&);


public:
    static ::java::lang::Class *class_();

private:
    void init();
    virtual ::java::lang::Class* getClass0();
    friend class MultiBandControls;
    friend class DualBandControls;
    friend class MultiBandCompressor_QuadBandControls;
};
