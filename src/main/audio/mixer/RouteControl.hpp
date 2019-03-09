#pragma once
#include <control/EnumControl.hpp>
#include <audio/mixer/MainMixControls.hpp>

#include <any>

namespace ctoot {
	namespace audio {
		namespace mixer {

			class RouteControl
				: public ctoot::control::EnumControl
			{

			private:
				MainMixControls* mmc;
				bool canRouteToGroups{};

			public:
				std::vector<std::any> getValues();
				
			public:
				RouteControl(MainMixControls* mmc, std::string defaultRoute, bool canRouteToGroups);

				friend class MainMixControls;
			};

		}
	}
}
