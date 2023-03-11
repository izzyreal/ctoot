#include <midi/core/DefaultConnectedMidiSystem.hpp>

#include <midi/core/MidiConnection.hpp>
#include <midi/core/MidiDevice.hpp>
#include <midi/core/MidiInput.hpp>
#include <midi/core/MidiOutput.hpp>
#include <midi/core/MidiPort.hpp>

// For find on armv7hf
#include <algorithm>

using namespace ctoot::midi::core;
using namespace std;

DefaultConnectedMidiSystem::DefaultConnectedMidiSystem() 
{
}

void DefaultConnectedMidiSystem::notifyObservers()
{
    checkConnections();
    super::notifyObservers();
}

void DefaultConnectedMidiSystem::checkConnections()
{
	vector<MidiInput*> inputs = getMidiInputs();
	vector<MidiOutput*> outputs = getMidiOutputs();
	vector<MidiConnection*> remove;
	for (auto& connection : connections) {
		auto input = connection->getMidiInput();
		auto output = connection->getMidiOutput();
		if (find(inputs.begin(), inputs.end(), input) != inputs.end() && find(outputs.begin(), outputs.end(), output) != outputs.end())	continue;
		remove.push_back(connection);
	}
	for (int i = (int)(remove.size()) - 1; i >= 0; i--) {
		connections.erase(connections.begin() + i);
	}
}

MidiConnection* DefaultConnectedMidiSystem::getConnection(MidiOutput* from, MidiInput* to)
{
	for (auto& c : connections) {
		if (c->getMidiOutput() == from && c->getMidiInput() == to) {
			return c;
		}
	}
	return nullptr;
	//    throw new ::java::lang::IllegalArgumentException(stringBuilder().append("MidiConnection from "->append(npc(from)->getName())
	//        ->append(" to "
	//        ->append(npc(to)->getName())->toString());
}

DefaultConnectedMidiSystem::~DefaultConnectedMidiSystem() {
	connections.clear();
}
