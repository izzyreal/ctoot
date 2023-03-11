#pragma once

#include <control/CompoundControl.hpp>

namespace ctoot::control {

    class ControlRow
            : public CompoundControl
    {

    public:
        typedef CompoundControl super;

    public:

        ControlRow();

    private:
        friend class CompoundControl;
    };
}
