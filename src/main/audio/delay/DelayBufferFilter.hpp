#pragma once


namespace ctoot {
	namespace audio {
		namespace delay {

			class DelayBuffer;

			class DelayBufferFilter
			{


			private:
				float zm1{ 0.0f };

			public:
				virtual float filter(float sample);
				
				DelayBufferFilter(DelayBuffer*);
                virtual ~DelayBufferFilter() {}
                
			private:
                const DelayBuffer* delayBuffer;
				
			};

		}
	}
}
