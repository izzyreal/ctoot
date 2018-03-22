#pragma once

#include <audio/filter/FilterSpecification.hpp>

namespace ctoot {
	namespace audio {
		namespace dynamics {

			class CrossoverControl;

			class CrossoverSection
				: public virtual ctoot::audio::filter::FilterSpecification
			{

			private:
				CrossoverControl* control{  };
				ctoot::dsp::filter::FilterShape shape{  };

			public:
				int32_t getFrequency() override;
				ctoot::dsp::filter::FilterShape getShape() override;
				float getResonance() override;
				float getLeveldB() override;
				float getLevelFactor() override;
				bool is4thOrder() override;
				void addObserver(moduru::observer::Observer* o) override;
				void deleteObserver(moduru::observer::Observer* o) override;

			public:
				CrossoverSection(CrossoverControl* control, ctoot::dsp::filter::FilterShape type);

			};

		}
	}
}
