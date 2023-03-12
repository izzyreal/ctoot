#pragma once

#include <observer/Observable.hpp>
#include <synth/MidiChannel.hpp>
#include <audio/core/ChannelFormat.hpp>

namespace ctoot::synth {

    class SynthChannel
            : public moduru::observer::Observable, public virtual MidiChannel
    {

    public:
        int sampleRate{44100};

    private:
        int pressure{0};
        std::vector<char> polyPressure = std::vector<char>(128);
        std::vector<char> controller = std::vector<char>(128);

    public:
        virtual void setLocation(std::string location) = 0;

        static float midiFreq(float pitch);

        static std::vector<float> &freqTable();

    private:
        static float midiFreqImpl(int pitch);

    public:
        virtual void setSampleRate(int rate);

        virtual std::weak_ptr<ctoot::audio::core::ChannelFormat> getChannelFormat();

    public:
        void noteOff(int pitch, int velocity) override;
        void controlChange(int arg0, int arg1) override;

        int getController(int arg0) override;

        int getProgram() override;

        void programChange(int arg0) override;

        void programChange(int arg0, int arg1) override;

        void setMono(bool mono) override;

        SynthChannel();

    public:
        virtual void noteOff(int noteNumber) override = 0;

    };
}
