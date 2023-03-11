#pragma once

#include <string>

namespace ctoot::audio::system {

    class AudioConnection
    {

    public:
        AudioConnection(int flags);

    private:
        int flags{0};

    public:
        virtual void close() = 0;

        virtual std::string getOutputName() = 0;

        virtual std::string getOutputLocation() = 0;

    };

}
