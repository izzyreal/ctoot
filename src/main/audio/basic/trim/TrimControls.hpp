#pragma once

#include <audio/core/AudioControls.hpp>
#include <control/LinearLaw.hpp>

#include <memory>

using namespace ctoot::audio::core;
using namespace ctoot::control;

namespace ctoot::audio::basic::trim {

	class TrimControls
		: public AudioControls {

	private:
		
		static std::weak_ptr<LinearLaw> TRIM_LAW() { 
			static std::shared_ptr<LinearLaw> trimLaw = std::make_shared<LinearLaw>(-20.f, 20.f, "dB");
			return trimLaw;
		};

		float trim = 1.f;

	public:
		float getTrim();

	public:
		TrimControls();

	};

}