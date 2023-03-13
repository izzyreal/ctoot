#pragma once

#include <control/AbstractLaw.hpp>

namespace ctoot::control {

    class LogLaw
            : public AbstractLaw
    {

    private:
        double logMin, logMax;
        double logSpan;

    public:
        int intValue(float userVal) override;

    public:
        LogLaw(float min, float max, std::string units);

    };

}
