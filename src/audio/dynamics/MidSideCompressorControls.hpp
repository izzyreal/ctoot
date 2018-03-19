#pragma once

#include <audio/core/AudioControls.hpp>
#include <audio/dynamics/MidSideDynamicsProcessVariables.hpp>

#include <memory>
#include <vector>

namespace ctoot {

	namespace control {
		class Control;
	}

	namespace audio {
		namespace dynamics {

			class MidSideCompressorControls
				: public ctoot::audio::core::AudioControls
				, public virtual MidSideDynamicsProcessVariables
			{
			private:
				void init();

			private:
				std::weak_ptr<CompressorControls> mid{  };
				std::weak_ptr<CompressorControls> side{  };
				std::vector<float> threshold{  };
				std::vector<float> inverseThreshold{  };
				std::vector<float> knee{  };
				std::vector<float> inverseRatio{  };
				std::vector<float> attack{  };
				std::vector<int32_t> hold{  };
				std::vector<float> release{  };
				std::vector<float> gain{  };
				std::vector<float> depth{  };

			protected:
				virtual void deriveIndependentVariables();
				virtual void deriveDependentVariables();
				void derive(ctoot::control::Control* c) override;

			public:
				void update(float sampleRate) override;
				std::vector<float> getThreshold() override;
				std::vector<float> getInverseThreshold() override;
				std::vector<float> getKnee() override;
				std::vector<float> getInverseRatio() override;
				std::vector<float> getAttack() override;
				std::vector<int32_t> getHold() override;
				std::vector<float> getRelease() override;
				std::vector<float> getGain() override;
				std::vector<float> getDepth() override;
				void setDynamicGain(float gainM, float gainS) override;

			public:
				MidSideCompressorControls();

			public:
				virtual bool isBypassed();

			};
		}
	}
}
