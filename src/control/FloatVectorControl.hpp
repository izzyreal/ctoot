#include "Control.hpp"

#include <vector>

namespace ctoot {

	namespace control {

		class FloatVectorControl
			: public Control

		{

		private:
			std::vector<float> values;

		public:
			void setValues(const std::vector<float>* values);
			void setValue(const int index, const float value);
			std::vector<float>* getValues();

		public:
			FloatVectorControl(int id, std::string name, int size);
			~FloatVectorControl();

		};
	}

}
