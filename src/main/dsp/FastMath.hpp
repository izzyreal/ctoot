#pragma once

namespace ctoot {
	namespace dsp {

		class FastMath
		{

		private:
			static constexpr float S_B{ 1.2732395f };
			static constexpr float S_C{ -0.40528473f };

		public:
			static float sin(float x);

		private:
			static constexpr float TWODIVPI{ 0.63661975f };

		public:
			static float triangle(float x);
			static float min(float a, float b);
			static float max(float a, float b);
			static float tanh(float x);

		};
	}
}
