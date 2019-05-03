#include <control/CompoundControlMidiPersistence.hpp>

#include <control/BypassControl.hpp>
#include <control/IntegerControl.hpp>
#include <control/CompoundControl.hpp>
#include <control/Control.hpp>
#include <control/automation/ControlSysexMsg.hpp>
#include <control/automation/MidiPersistence.hpp>

#include <file/FileUtil.hpp>
#include <file/Directory.hpp>
#include <file/FsNode.hpp>


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

void removeExtension(std::string& path) {
	const auto index = path.find(".mbc");
	if (index != std::string::npos)
		path.erase(path.begin() + index, path.end());
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
			auto name = f->getName();
			m.emplace(name, node);
		}
		else {
			PresetTreeNode node;
			string parentPath = dir->getPath();

			std::string::size_type i = parentPath.find(rootPath);

			if (i != std::string::npos)
				parentPath.erase(i, rootPath.length());

			node.parentPath = parentPath;

			auto name = f->getName();
			removeExtension(name);
			m.emplace(name, node);
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
//    auto providerId = cl->getProviderId();
//    auto moduleId = cl->getId();

	Directory rootDir(rootPath, nullptr);
	auto finalName = rootDir.getPath() + name + ".mbc";

	MLOG("finalName to load: " + finalName);

	auto file = make_unique<File>(finalName, nullptr);

	if (!file->exists())
		return;
	std::vector<char> vec(file->getLength());
	file->getData(&vec);
	setStateFromVector(vec, c);
}

void CompoundControlMidiPersistence::getStateAsVector(vector<char>& vec, weak_ptr<CompoundControl> c) {
	auto state = getStateAsMidiFile(c);
	state->writeToArray(vec);
	delete state;
}

void CompoundControlMidiPersistence::setStateFromVector(vector<char>& vec, weak_ptr<CompoundControl> c) {

	auto cl = c.lock();
	if (!cl) return;
	auto providerId = cl->getProviderId();
	auto moduleId = cl->getId();

	auto sequence = new smf::MidiFile();
	sequence->readFromArray(vec);
	auto eventCount = sequence->getNumEvents(0);
	for (int i = 0; i < eventCount; i++) {
		auto msg = sequence->getEvent(0, i);
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
			//MLOG("no control deepFound, controlId in event data is " + to_string(ControlSysexMsg::getControlId(dataVec)));
			continue;
		}

		if (dynamic_pointer_cast<BypassControl>(control)) {
			continue;
		}
		auto v = ControlSysexMsg::getValue(dataVec);
		control->setIntValue(v);
	}
}

void CompoundControlMidiPersistence::savePreset(weak_ptr<CompoundControl> c, const string& name)
{
	
	auto state = getStateAsMidiFile(c);
	Directory rootDir(rootPath, nullptr);
	if (!rootDir.exists()) rootDir.create();
	File f(rootDir.getPath() + name + ".mbc", nullptr);
	MLOG("Trying to write sequence to path " + f.getPath());
	state->write(f.getPath());
	delete state;
}

MidiFile* CompoundControlMidiPersistence::getStateAsMidiFile(weak_ptr<CompoundControl> c) {
	auto cl = c.lock();
	auto providerId = cl->getProviderId();
	auto moduleId = cl->getId();

	MidiFile* m = new MidiFile();
	m->addTrack();
	MidiPersistence::store(providerId, moduleId, 0, c, *m);

	for (int i = 0; i < 128; i++) {
		if (MidiPersistence::eventSet.find(i) == MidiPersistence::eventSet.end()) {
			//MLOG("id " + to_string(i) + " is still available");
		}
	}
	return m;
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
