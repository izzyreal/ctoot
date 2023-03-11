#pragma once

#include <control/LawControl.hpp>

namespace ctoot::control {

    class FloatControl
            : public LawControl
    {

    private:
        std::string minLabel;
        std::string maxLabel;
        std::string midLabel;

    public:
        virtual float getMaximum();

        virtual float getMinimum();

    public:
        FloatControl(int id, std::string name, std::weak_ptr<ControlLaw> law, float precision, float initialValue);

    };

}
