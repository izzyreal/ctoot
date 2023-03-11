#pragma once
#include <control/Control.hpp>
#include <cstdint>
#include <string>

#include <thirdp/any.hpp>

namespace ctoot {
	namespace control {
		class EnumControl
			: public Control
		{
		private:
			nonstd::any value;

		public:
			virtual void setValue(nonstd::any value);
			virtual nonstd::any getValue();
			virtual std::vector<nonstd::any> getValues() = 0;
			virtual bool isValueSupported(nonstd::any value);

		public:
			std::string toString();
			virtual int getWidthLimit();

        public:
			std::string getValueString() override;
			void setIntValue(int value) override;
			int getIntValue() override;

		public:
			EnumControl(int id, std::string name, nonstd::any value);

		};

	}
}
