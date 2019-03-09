#pragma once
#include <memory>
#include <set>

namespace smf {
	class MidiFile;
}

namespace ctoot {
	namespace control {

		class CompoundControl;

		namespace automation {

			class MidiPersistence
			{

			public:
				static void store(int32_t providerId, int32_t moduleId, int32_t instanceIndex, std::weak_ptr<ctoot::control::CompoundControl> parent, smf::MidiFile& midiFile);
				static int eventCounter;
				static std::set<int> eventSet;

			public:
				MidiPersistence();

			};

		}
	}
}
