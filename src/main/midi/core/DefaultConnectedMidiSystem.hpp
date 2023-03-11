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
                void createMidiConnection(MidiOutput* from, MidiInput* to, int flags) override;
				void closeMidiConnection(MidiOutput* from, MidiInput* to) override;

            public:
				virtual MidiConnection* getConnection(MidiOutput* from, MidiInput* to);
				virtual MidiPort* getPort(std::string* name, bool isOut);

			public:
				DefaultConnectedMidiSystem();
				~DefaultConnectedMidiSystem();

			};

		}
	}
}
