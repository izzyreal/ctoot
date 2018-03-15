#pragma once
#include <audio/core/AudioControls.hpp>

#include <control/LinearLaw.hpp>

#include <vector>

namespace ctoot {
	namespace audio {
		namespace delay {
			
			class DelayTap;

			class MultiTapDelayControls
				: public ctoot::audio::core::AudioControls
			{

			private:
				static std::weak_ptr<ctoot::control::ControlLaw> LAW(float msMax);

			private:
				std::vector<std::weak_ptr<DelayTap>> taps;

			public:
				virtual std::vector<std::weak_ptr<DelayTap>> getTaps();
				bool isNeverBordered() override;
				//std::string getAlternate() override;

			public:
				MultiTapDelayControls(int idOffset, int ntaps, float msMax, std::string name);

			};

		}
	}
}
