#pragma once


namespace ctoot {
	namespace audio {
		namespace delay {

			class PhaserProcessVariables
				
			{
			public:
				virtual bool isBypassed() = 0;
				virtual int getStages() = 0;
				virtual float getRate() = 0;
				virtual float getDepth() = 0;
				virtual float getFeedback() = 0;
			};

		}
	}
}
