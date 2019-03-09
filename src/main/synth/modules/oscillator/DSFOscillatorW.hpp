#pragma once

#include <synth/modules/oscillator/DSFOscillator.hpp>

#include <memory>

namespace ctoot {

	namespace dsp {
		class Sine;
		class Cosine;
	}

	namespace synth {
		namespace modules {
			namespace oscillator {

				class DSFOscillatorW
					: public virtual DSFOscillator
				{

				private:
					double a{  };
					std::shared_ptr<ctoot::dsp::Sine> sine1{  };
					std::shared_ptr<ctoot::dsp::Sine> sine2{  };
					std::shared_ptr<ctoot::dsp::Sine> sine3{  };
					std::shared_ptr<ctoot::dsp::Cosine> cosine{  };
					double aN{  };
					int32_t np{  };

				public:
					void update(float a) override;
					float getSample() override;

					DSFOscillatorW(double wn, double wp, int32_t np, float a);
				};

			}
		}
	}
}
