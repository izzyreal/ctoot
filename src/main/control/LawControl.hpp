#pragma once

#include <control/Control.hpp>
#include <control/ControlLaw.hpp>

#include <memory>

namespace ctoot::control {

    class LawControl
            : public Control
    {

    private:
        std::weak_ptr<ControlLaw> law;
        float value{0};
        float precision{0};

    public:
        virtual float getValue();

        virtual void setValue(float value);

    public:
        int getIntValue() override;

        std::string getValueString() override;

    public:
        LawControl(int id, std::string name, std::weak_ptr<ControlLaw> law, float precision, float initialValue);

    };

}
