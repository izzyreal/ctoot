#pragma once
#include <control/CompoundControl.hpp>

#include <string>
#include <vector>

namespace ctoot {
	namespace synth {

		class SynthControls;

		class SynthRackControls
			: public ctoot::control::CompoundControl
		{

		private:
			std::vector<std::weak_ptr<SynthControls>> synthControls{};
			int nsynths{ 0 };

		public:
			virtual int size();
			virtual std::weak_ptr<SynthControls> getSynthControls(int synth);
			virtual void setSynthControls(int synth, std::shared_ptr<SynthControls> controls);

            int getProviderId() override;

			SynthRackControls(int nsynths);
		};

	}
}
