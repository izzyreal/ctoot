#pragma once

#include <audio/system/AudioDevice.hpp>

namespace ctoot::audio::system {

    class AbstractAudioDevice
            : public virtual AudioDevice
    {

    public:
        std::vector<std::shared_ptr<AudioInput>> inputs{};
        std::vector<std::shared_ptr<AudioOutput>> outputs{};

    private:
        std::string name;

    public:
        std::vector<std::weak_ptr<AudioOutput>> getAudioOutputs() override;

        std::string getName() override;

        std::string toString();

    };

}
