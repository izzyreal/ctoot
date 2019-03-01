#pragma once

#include <observer/Observer.hpp>

namespace ctoot {
	namespace audio {
		namespace filter {

			class AbstractFilter;

			class AbstractFilterObserver
				: public virtual moduru::observer::Observer
			{

			public:
				void update(moduru::observer::Observable* obs, std::any arg) override;

			public:
				AbstractFilterObserver(AbstractFilter* af);

			private:
				AbstractFilter* af;

			};

		}
	}
}
