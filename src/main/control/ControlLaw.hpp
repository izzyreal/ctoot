#pragma once

#include <cstdint>
#include <string>

namespace ctoot::control {

    class ControlLaw
    {

    public:
        virtual int intValue(float userVal);

        virtual float getMinimum();

        virtual float getMaximum();

        virtual std::string getUnits();

    };
}
