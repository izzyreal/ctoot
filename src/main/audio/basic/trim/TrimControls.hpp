#pragma once

#include <audio/core/AudioControls.hpp>
#include <control/LinearLaw.hpp>

#include <memory>

using namespace ctoot::audio::core;
using namespace ctoot::control;
using namespace std;

namespace ctoot::audio::basic::trim {

	class TrimControls
		: public AudioControls {

	private:
		
		static weak_ptr<LinearLaw> TRIM_LAW() { 
			static shared_ptr<LinearLaw> trimLaw = make_shared<LinearLaw>(-20.f, 20.f, "dB");
			return trimLaw;
		};

		float trim = 1.f;

	public:
		float getTrim();

	public:
		TrimControls();
		~TrimControls();

	};

}