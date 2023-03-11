#pragma once

#include <control/Control.hpp>
#include <cstdint>
#include <string>

#include <thirdp/any.hpp>

namespace ctoot::control {
    class EnumControl
            : public Control
    {
    private:
        nonstd::any value;

    public:
        virtual void setValue(nonstd::any value);

        virtual nonstd::any getValue();

        virtual std::vector<nonstd::any> getValues() = 0;

        virtual bool isValueSupported(nonstd::any value);

    public:
        std::string toString();

    public:
        std::string getValueString() override;

        int getIntValue() override;

    public:
        EnumControl(int id, std::string name, nonstd::any value);

    };

}
