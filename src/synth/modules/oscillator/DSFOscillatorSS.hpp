#pragma once

#include <synth/modules/oscillator/DSFOscillator.hpp>

#include <cstdint>
#include <memory>


namespace ctoot {

	namespace dsp {
		class Sine;
	}

	namespace synth {
		namespace modules {
			namespace oscillator {

				class DSFOscillatorSS
					: public virtual DSFOscillator
				{

				private:
					double a{  };
					int32_t np{  };
					std::shared_ptr<ctoot::dsp::Sine> s1{  };
					std::shared_ptr<ctoot::dsp::Sine> s2{  };
					std::shared_ptr<ctoot::dsp::Sine> s3{  };
					std::shared_ptr<ctoot::dsp::Sine> s4{  };
					std::shared_ptr<ctoot::dsp::Cosine> cosine{  };
					double aNm1{  };

				public:
					void update(float a) override;
					float getSample() override;

					DSFOscillatorSS(double wn, double wp, int32_t np, float a);

				};

			}
		}
	}
}
