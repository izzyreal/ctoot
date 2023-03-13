#pragma once

#include <audio/server/AudioClient.hpp>

#include <vector>
#include <memory>

namespace ctoot::audio::server {

    class CompoundAudioClient final
            : public AudioClient
    {

    private:
        std::vector<AudioClient *> clients;

    public:
        void work(int nFrames) override;

        void add(AudioClient *client);

        void remove(AudioClient *client);
    };

}
