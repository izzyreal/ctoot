#pragma once

#include <control/FloatControl.hpp>
#include <control/ControlLaw.hpp>

#include <string>
#include <memory>

using namespace ctoot::control;

using namespace std;

namespace ctoot::audio::basic::trim {

	class TrimControl
		: public FloatControl {

	private:
		float* trimToSet;

	protected:
		void derive(Control* control) override;

	public:
		TrimControl(int id, string name, weak_ptr<ControlLaw> law, float precision, float initialValue, float* trimToSet);
		~TrimControl();

	};

}