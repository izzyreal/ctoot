#pragma once

#include <control/FloatControl.hpp>
#include <control/ControlLaw.hpp>

#include <string>
#include <memory>

using namespace ctoot::control;

namespace ctoot::audio::basic::trim {

	class TrimControl
		: public FloatControl {

	private:
		float* trimToSet;

	protected:
		void derive(Control* control) override;

	public:
		TrimControl(int id, std::string name, std::weak_ptr<ControlLaw> law, float precision, float initialValue, float* trimToSet);
		~TrimControl();

	};

}