#pragma once
#include <midi/core/DefaultMidiSystem.hpp>
#include <midi/core/ConnectedMidiSystem.hpp>

namespace ctoot {
	namespace midi {
		namespace core {

			class MidiPort;

			class DefaultConnectedMidiSystem final
				: public DefaultMidiSystem
				, public virtual ConnectedMidiSystem
			{

			public:
				typedef DefaultMidiSystem super;

			private:
				std::vector<MidiConnection*> connections{};

			public:
				void notifyObservers() override;

			public:
				virtual void checkConnections();

            public:
				virtual MidiConnection* getConnection(MidiOutput* from, MidiInput* to);

            public:
				DefaultConnectedMidiSystem();
				~DefaultConnectedMidiSystem();

			};

		}
	}
}
