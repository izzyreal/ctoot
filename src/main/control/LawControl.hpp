#pragma once

#include <control/Control.hpp>
#include <control/ControlLaw.hpp>

#include <memory>

namespace ctoot {
	namespace control {

		class LawControl
			: public Control
		{

		private:
			std::weak_ptr<ControlLaw> law;
			float value{ 0 };
			float precision{ 0 };

		public:
			virtual int calculateDecimalPlaces();

		public:
			virtual std::weak_ptr<ControlLaw> getLaw();
			virtual float getValue();
			virtual void setValue(float value);
			virtual float getPrecision();
			virtual std::vector<std::string> getPresetNames();
			virtual void applyPreset(std::string name);

		public:
			int getIntValue() override;
			std::string getValueString() override;
			void setIntValue(int value) override;

		public:
			LawControl(int id, std::string name, std::weak_ptr<ControlLaw> law, float precision, float initialValue);
			virtual ~LawControl();

		};

	}
}
