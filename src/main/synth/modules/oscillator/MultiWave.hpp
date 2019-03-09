#pragma once

#include <vector>
#include <memory>

namespace ctoot {
	namespace synth {
		namespace modules {
			namespace oscillator {

				class Wave;

				class MultiWave
				{

				protected:
					std::vector<std::shared_ptr<Wave>> wave = std::vector<std::shared_ptr<Wave>>(128);

				private:
					static std::vector<int> index;

				protected:
					std::vector<float> sinetable{  };

				protected:
					virtual void createIndex();
					virtual void createWaves(int32_t size, float fNyquist);
					virtual int32_t partial(std::vector<float>* data, int32_t length, int32_t partial, int32_t sign, float comp) = 0;
					virtual float getMax(std::vector<float>* data);
					virtual void normalise(std::vector<float>* data, float max);

				public:
					virtual int32_t getIndex(float freq);
					virtual std::weak_ptr<Wave> getWave(int32_t n);
					virtual float getWidthStartFactor(float width);
					virtual float getWidthScalar(float width);
					virtual float getWidthOffset(float width);

				public:
					MultiWave();
					void init(int32_t size, float fNyquist);

				};

			}
		}
	}
}
