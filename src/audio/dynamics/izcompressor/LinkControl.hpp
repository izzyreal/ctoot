#pragma once

#include <control/IntegerControl.hpp>

#include <memory>
#include <vector>

namespace ctoot {
	namespace audio {
		namespace dynamics {
			namespace izcompressor {

				class IzBandCompressorControls;

				class LinkControl
					: public ctoot::control::IntegerControl
				{

				private:
					std::vector<std::weak_ptr<IzBandCompressorControls>> controls;

				public:
					void setValue(float value) override;

				public:
					LinkControl(int idOffset, std::string name, std::weak_ptr<ctoot::control::IntegerLaw> law, std::vector<std::weak_ptr<IzBandCompressorControls>> controls);

				};

			}
		}
	}
}
