#include "FloatVectorControl.hpp"

using namespace ctoot::control;
using namespace std;

FloatVectorControl::~FloatVectorControl() {
}

vector<float>* FloatVectorControl::getValues() {
	return &values;
}

void FloatVectorControl::setValues(const std::vector<float>* values) {
	this->values = *values;
}

void FloatVectorControl::setValue(int index, const float value) {

	if (index > values.size() - 1) return;

	values[index] = value;

}
