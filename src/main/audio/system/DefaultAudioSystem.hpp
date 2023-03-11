#pragma once

#include <audio/system/AudioSystem.hpp>

#include <memory>

namespace ctoot::audio::system {

    class DefaultAudioSystem
            : public AudioSystem
    {

    protected:
        std::vector<std::weak_ptr<AudioDevice>> devices{};

    public:
        virtual void checkUniqueDeviceName(std::weak_ptr<AudioDevice> device);

    public:
        void addAudioDevice(std::weak_ptr<AudioDevice> device) override;

        void removeAudioDevice(std::weak_ptr<AudioDevice> device) override;

        void close() override;

    public:
        DefaultAudioSystem();

    };

}
