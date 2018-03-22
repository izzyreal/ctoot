#pragma once

#include <audio/filter/Filter.hpp>

#include <observer/Observer.hpp>

namespace ctoot {
	namespace audio {
		namespace filter {

			class FilterSpecification;
			class FilterDesign;
			class FilterState;

			class AbstractFilter
				: public virtual Filter
			{

			private:
				FilterDesign * design{  };
				moduru::observer::Observer* specObserver{  };
				bool doUpdate{  };
				static constexpr int32_t MAX_CHANNELS{ int32_t(6) };
				std::vector<FilterState*> states{  };

			protected:
				float amplitudeAdj{  };
				int32_t sampleRate{  };

			private:
				float levelOffset{  };

			public:
				void open() override;
				void close() override;
				virtual FilterDesign* getDesign();
				void clear() override;

			protected:
				virtual FilterState* getState(int32_t chan);

			public:
				void setSampleRate(int32_t rate) override;

			protected:
				virtual FilterDesign* createDesign(FilterSpecification* spec) = 0;
				virtual FilterState* createState() = 0;
				virtual void updateFilterCoefficients() = 0;

			public:
				AbstractFilter(FilterSpecification* spec, bool relative);

			private:
				void init();

			private:
				friend class AbstractFilterObserver;
			};

		}
	}
}
