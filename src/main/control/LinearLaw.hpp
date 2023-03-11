#pragma once
#include <control/AbstractLaw.hpp>
#include <string>

#include <memory>

namespace ctoot {
	namespace control {

		class LinearLaw
			: public AbstractLaw
		{

		public:
			int intValue(float v) override;

            LinearLaw(float min, float max, std::string units);
            virtual ~LinearLaw() override {}
            
		public:
			static std::weak_ptr<LinearLaw> UNITY();

		};
	}
}
