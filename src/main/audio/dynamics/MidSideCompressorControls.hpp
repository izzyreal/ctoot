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

			class CompressorControls;

			class MidSideCompressorControls
				: public ctoot::audio::core::AudioControls
				, public virtual MidSideDynamicsProcessVariables
			{

			private:
				std::weak_ptr<CompressorControls> mid{  };
				std::weak_ptr<CompressorControls> side{  };
				std::vector<float> threshold = std::vector<float>(2);
				std::vector<float> inverseThreshold = std::vector<float>(2);
				std::vector<float> knee = std::vector<float>(2);
				std::vector<float> inverseRatio = std::vector<float>(2);
				std::vector<float> attack = std::vector<float>(2);
				std::vector<int32_t> hold = std::vector<int32_t>(2);
				std::vector<float> release = std::vector<float>(2);
				std::vector<float> gain = std::vector<float>(2);
				std::vector<float> depth = std::vector<float>(2);

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
				MidSideCompressorControls(std::string band);

			public:
				virtual bool isBypassed() override;

			};
			REGISTER_TYPE(ctoot::audio::dynamics::, MidSideCompressorControls)
		}
	}
}
