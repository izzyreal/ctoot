#pragma once


namespace ctoot {
	namespace audio {
		namespace delay {

			class DelayBuffer;

			class DelayBuffer_Filter
			{


			private:
				float zm1{ 0.0f };

			public:
				virtual float filter(float sample);
				
				DelayBuffer_Filter(DelayBuffer *DelayBuffer_this);
				
			private:
				DelayBuffer *DelayBuffer_this;
				
			};

		}
	}
}
