#pragma once

namespace ctoot {
	namespace dsp {

		class Phasor
		{

		private:
			double y0{  }, y1{  }, y2{  };
			double b1{  };

		public:
			float out();

		public:
			Phasor(double w, double theta);

		};

	}
}
