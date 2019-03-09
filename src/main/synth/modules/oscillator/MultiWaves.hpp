#pragma once

#include <vector>
#include <string>
#include <memory>

namespace ctoot {
	namespace synth {
		namespace modules {
			namespace oscillator {

				class MultiWave;

				class MultiWaves
				{

				private:
					static std::string SQUARE;
					static std::string SAW;
					static std::shared_ptr<MultiWave> square;
					static std::shared_ptr<MultiWave> saw;
					static int32_t size;
					static std::vector<std::string> names;

				public:
					static std::vector<std::string> getNames();
					static void init();
					static std::weak_ptr<MultiWave> get(std::string name);
					static void setSize(int32_t aSize);
					static std::shared_ptr<MultiWave> createSquareWave(int32_t nsamples);
					static std::shared_ptr<MultiWave> createSawtoothWave(int32_t nsamples);

				};

			}
		}
	}
}
