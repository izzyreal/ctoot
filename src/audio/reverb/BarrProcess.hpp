#pragma once
#include "AbstactReverbProcess.hpp"

#include <memory>

namespace ctoot {
	namespace audio {
		namespace reverb {

			class BarrVariables {

			public:
				//virtual bool isBypassed() = 0;
				virtual int getPreDelaySamples() = 0;
				virtual float getBandwidth() = 0;       // 0..1
				virtual float getInputDiffusion() = 0; // 0..1
				virtual float getDecayDiffusion() = 0; // 0..1
				virtual float getDamping() = 0;         // 0..1
				virtual float getDecay() = 0;           // 0..1
				virtual float getSize() = 0;            // >0..1

														// following methods are called once at startup
				virtual int getMaxPreDelaySamples() = 0;
				virtual std::vector<std::vector<int>> getSizes() = 0;         // [block][3|4] (dif1, dif2, del)|(id1, id2, id3, id4)
				virtual std::vector<std::vector<int>> getLeftTaps() = 0;      // [block][2]
				virtual std::vector<std::vector<int>> getRightTaps() = 0;     // [block][2]

			};

			class Block
			{
			private:
				Diffuser dif1, dif2;
				Delay del;
				std::vector<int> tapsLeft, tapsRight, tl, tr;

			public:
				Block();
				Block(std::vector<int> sz, std::vector<int> left, std::vector<int> right);

			public:
				float tick(float sample, float decay, float decayDiffusion);
				float left();
				float right();
				void resize(float factor);

			private:
				void calcTaps(float size);
			};

			class BarrProcess
				: public AbstractReverbProcess
			{

			public:
				BarrProcess(std::weak_ptr<BarrVariables> vars);
				~BarrProcess();

			private:
				const static float GAIN_8;
				std::weak_ptr<BarrVariables> vars;
				float zm1 = 0.f;
				Block block1, block2, block3, block4;
				Filter damp1, damp2;

				Delay ipd;
				Filter bw;
				Diffuser id1a, id1b, id2a, id2b;

				int preDelaySamples;
				float bandwidth;
				float inputDiffusion;
				float damping, decay;
				float decayDiffusion;
				float size, prevSize = 1.f;
				bool halfInserts = false;

			protected:
				void cacheVariables() override;
				void reverb(float left, float right) override;
				float left() override;
				float right() override;

			protected:
				float idiffuse(float sample);

			};
		}
	}
}
