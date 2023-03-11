#pragma once

#include <control/EnumControl.hpp>
#include <audio/mixer/MainMixControls.hpp>

#include <thirdp/any.hpp>

namespace ctoot::audio::mixer {

    class RouteControl
            : public ctoot::control::EnumControl
    {

    private:
        MainMixControls *mmc;
        bool canRouteToGroups{};

    public:
        std::vector<nonstd::any> getValues();

    public:
        RouteControl(MainMixControls *mmc, std::string defaultRoute, bool canRouteToGroups);

        friend class MainMixControls;
    };

}
