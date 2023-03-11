#pragma once

#include "MidiMsg.hpp"

namespace ctoot::midi::message {

    class SysexMsg
            : public MidiMsg
    {

    public:

        static const unsigned char SYSTEM_EXCLUSIVE{240};
        static const unsigned char ID_NON_COMMERCIAL{125};

    };

}
