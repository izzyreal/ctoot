#pragma once

#include <audio/core/AudioProcess.hpp>
#include <audio/core/AudioControlsChain.hpp>
#include <audio/core/AudioControls.hpp>

#include <observer/Observer.hpp>
#include <thirdp/concurrentqueue.h>

#include <cstdint>

namespace ctoot::audio::core {

    class AudioProcessChain
            : public virtual AudioProcess
    {

    public:
        std::weak_ptr<AudioControlsChain> controlChain;
        std::vector<std::shared_ptr<AudioProcess>> processes;

    public:
        void open() override;

    public:
        int processAudio(ctoot::audio::core::AudioBuffer *buffer, int nFrames) override;

        void close() override;

        virtual std::string getName();

    public:
        virtual std::shared_ptr<AudioProcess> createProcess(std::weak_ptr<AudioControls> controls);

    public:
        AudioProcessChain(std::weak_ptr<AudioControlsChain> controlChain);

    };

}
