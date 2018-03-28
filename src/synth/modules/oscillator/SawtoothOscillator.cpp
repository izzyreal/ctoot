// Generated from /toot2/src/uk/org/toot/synth/modules/oscillator/SawtoothOscillator.java
#include <synth/modules/oscillator/SawtoothOscillator.hpp>

#include <java/lang/NullPointerException.hpp>
#include <java/lang/String.hpp>
#include <synth/SynthChannel.hpp>
#include <synth/modules/oscillator/MultiWave.hpp>
#include <synth/modules/oscillator/MultiWaves.hpp>
#include <synth/modules/oscillator/Wave.hpp>
#include <Array.hpp>

template<typename T>
static T* npc(T* t)
{
    if(!t) throw new ::java::lang::NullPointerException();
    return t;
}

 ctoot::synth::modules::oscillator::SawtoothOscillator::SawtoothOscillator(const ::default_init_tag&)
    : super(*static_cast< ::default_init_tag* >(0))
{
    clinit();
}

 ctoot::synth::modules::oscillator::SawtoothOscillator::SawtoothOscillator(ctoot::synth::SynthChannel* channel, float frequency) 
    : SawtoothOscillator(*static_cast< ::default_init_tag* >(0))
{
    ctor(channel,frequency);
}

void modules::oscillator::SawtoothOscillator::init()
{
    increment = 1.0f;
    index = 0.0f;
}

 ctoot::synth::modules::oscillator::MultiWave*& ctoot::synth::modules::oscillator::SawtoothOscillator::multiWave()
{
    clinit();
    return multiWave_;
}
 ctoot::synth::modules::oscillator::MultiWave* ctoot::synth::modules::oscillator::SawtoothOscillator::multiWave_;

void modules::oscillator::SawtoothOscillator::ctor(ctoot::synth::SynthChannel* channel, float frequency)
{
    super::ctor();
    init();
    this->channel = channel;
    this->frequency = frequency;
    waveIndex = npc(multiWave_)->getIndex(frequency);
    wave = npc(multiWave_)->getWave(waveIndex);
    waveSize = npc(npc(wave)->getData())->length - int32_t(1);
    k = npc(wave)->getPeriod() * frequency;
}

void modules::oscillator::SawtoothOscillator::setSampleRate(int32_t sampleRate)
{
    increment = k / sampleRate;
    k2 = frequency / increment;
}

void modules::oscillator::SawtoothOscillator::update()
{
    currentIncrement = increment * npc(channel)->getBendFactor();
}

float ctoot::synth::modules::oscillator::SawtoothOscillator::getSample(float mod)
{
    auto inc = currentIncrement * mod;
    auto sample = npc(wave)->get(index);
    index += inc;
    if(index >= waveSize) {
        index -= waveSize;
        auto wi = npc(multiWave_)->getIndex(k2 * inc);
        if(wi != waveIndex) {
            wave = npc(multiWave_)->getWave(wi);
            waveIndex = wi;
        }
    }
    return sample;
}

extern java::lang::Class *class_(const char16_t *c, int n);

java::lang::Class* ctoot::synth::modules::oscillator::SawtoothOscillator::class_()
{
    static ::java::lang::Class* c = ::class_("uk.org.toot.synth.modules.oscillator.SawtoothOscillator", 55);
    return c;
}

void modules::oscillator::SawtoothOscillator::clinit()
{
    super::clinit();
    static bool in_cl_init = false;
struct clinit_ {
    clinit_() {
        in_cl_init = true;
        {
            multiWave_ = MultiWaves::get("Square");
        }
    }
};

    if(!in_cl_init) {
        static clinit_ clinit_instance;
    }
}

java::lang::Class* ctoot::synth::modules::oscillator::SawtoothOscillator::getClass0()
{
    return class_();
}

