#include <control/CompoundControlMidiPersistence.hpp>

#include <control/BypassControl.hpp>
#include <control/CompoundControl.hpp>
#include <control/Control.hpp>
#include <control/automation/ControlSysexMsg.hpp>
#include <control/automation/MidiPersistence.hpp>

#include <file/FileUtil.hpp>
#include <file/Directory.hpp>
#include <file/FsNode.hpp>

#include <thirdp/midifile/MidiFile.h>

using namespace ctoot::control;
using namespace ctoot::control::automation;
using namespace moduru::file;
using namespace std;
using namespace smf;

CompoundControlMidiPersistence::CompoundControlMidiPersistence(const string& rootPath)
{
	this->rootPath = rootPath;
}

vector<string> CompoundControlMidiPersistence::getPresets()
{
	vector<string> res;	
	auto dir = make_unique<Directory>(rootPath, nullptr);
	
	if (!dir->exists() || !dir->isDirectory()) {
		MLOG(dir->getName() + " does not exist or is not a directory");
		return res;
	}

	auto files = dir->listFiles();
	for (auto& file : files) {

		if (file->isDirectory())
			continue;

		res.push_back(file->getName());
	}
	return res;
}

void CompoundControlMidiPersistence::addDirContents(map<string, PresetTreeNode>& m, shared_ptr<Directory> dir) {
	for (auto& f : dir->listFiles()) {
		if (f->isDirectory()) {
			PresetTreeNode node;
			node.directory = true;
			string parentPath = dir->getPath();

			std::string::size_type i = parentPath.find(rootPath);

			if (i != std::string::npos)
				parentPath.erase(i, rootPath.length());

			node.parentPath = parentPath;
			addDirContents(node.node, dynamic_pointer_cast<Directory>(f));
			m.emplace(f->getName(), node);
			//MLOG("addDirContents added dir " + f->getName());
		}
		else {
			PresetTreeNode node;
			string parentPath = dir->getPath();

			std::string::size_type i = parentPath.find(rootPath);

			if (i != std::string::npos)
				parentPath.erase(i, rootPath.length());

			node.parentPath = parentPath;

			m.emplace(f->getName(), node);
			//MLOG("addDirContents added file " + f->getName());
		}
	}
}

PresetTreeNode CompoundControlMidiPersistence::getPresetsRecursive() {
	auto dir = make_shared<Directory>(rootPath, nullptr);
	PresetTreeNode res;
	addDirContents(res.node, dir);
	return res;
}

void CompoundControlMidiPersistence::loadPreset(weak_ptr<CompoundControl> c, const string& name)
{
	auto cl = c.lock();
	if (!cl) return;
	auto providerId = cl->getProviderId();
	auto moduleId = cl->getId();

	Directory rootDir(rootPath, nullptr);
	auto finalName = rootDir.getPath() + name;

	MLOG("finalName to load: " + finalName);

	auto file = make_unique<File>(finalName, nullptr);

	if (!file->exists())
		return;

	auto sequence = smf::MidiFile();
	sequence.read(file->getPath());
	auto eventCount = sequence.getNumEvents(0);
	for (int i = 0; i < eventCount; i++) {
		auto msg = sequence.getEvent(0, i);
		auto data = msg.data();
		vector<char> dataVec(msg.size());
		for (int i = 0; i < msg.size(); i++) {
			dataVec[i] = data[i];
		}

		if (!ControlSysexMsg::isControl(dataVec)) {
			MLOG("event is not a control");
			continue;
		}

		if (ControlSysexMsg::getProviderId(dataVec) != providerId) {
			MLOG("no providerId match");
			continue;
		}

		if (ControlSysexMsg::getModuleId(dataVec) != moduleId) {
			MLOG("no moduleId match");
			continue;
		}

		auto control = cl->deepFind(ControlSysexMsg::getControlId(dataVec)).lock();

		if (!control) {
			MLOG("no control deepFound, controlId in event data is " + to_string(ControlSysexMsg::getControlId(dataVec)));
			continue;
		}

		if (dynamic_pointer_cast<BypassControl>(control)) {
			MLOG("control is a BypassControl");
			continue;
		}
		auto v = ControlSysexMsg::getValue(dataVec);
		//MLOG("preset loading setting int value " + to_string(v) + " for control " + control->getName());
		control->setIntValue(v);
	}
}

void CompoundControlMidiPersistence::savePreset(weak_ptr<CompoundControl> c, const string& name)
{
	auto cl = c.lock();
	auto providerId = cl->getProviderId();
	auto moduleId = cl->getId();
	//auto sequence = new ::javax::sound::midi::Sequence(::javax::sound::midi::Sequence::PPQ, int(1));
	
	MidiFile sequence;

	sequence.addTrack();
	MidiPersistence::store(providerId, moduleId, 0, c, sequence);

	Directory rootDir(rootPath, nullptr);
	if (!rootDir.exists()) rootDir.create();
	File f(rootDir.getPath() + name, nullptr);
	MLOG("Trying to write sequence to path " + f.getPath());
	sequence.write(f.getPath());
}

string CompoundControlMidiPersistence::getPath(weak_ptr<CompoundControl> c)
{
	auto cl = c.lock();
	auto sep = moduru::file::FileUtil::getSeparator();
	if (cl) {
		return string(cl->getPersistenceDomain() + sep + to_string(cl->getProviderId()) + sep + to_string(cl->getId()));
	}
	return {};
}
