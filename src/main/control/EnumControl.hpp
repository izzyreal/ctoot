#pragma once
#include <control/Control.hpp>
#include <cstdint>
#include <string>

#include <any>

namespace ctoot {
	namespace control {
		class EnumControl
			: public Control
		{
		private:
			std::any value;

		public:
			virtual void setValue(std::any value);
			virtual std::any getValue();
			virtual std::vector<std::any> getValues() = 0;
			virtual bool isValueSupported(std::any value);

		public:
			std::string toString();
			virtual int getWidthLimit();
			virtual bool hasLabel();

		public:
			std::string getValueString() override;
			void setIntValue(int value) override;
			int getIntValue() override;

		public:
			EnumControl(int id, std::string name, std::any value);

		};

	}
}
