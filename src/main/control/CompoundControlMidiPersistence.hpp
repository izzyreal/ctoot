#pragma once
#include <control/CompoundControl.hpp>
#include <control/CompoundControlPersistence.hpp>

#include <file/File.hpp>

#include <thirdp/midifile/MidiFile.h>

namespace ctoot {
	namespace control {
		class CompoundControlMidiPersistence
			: public virtual CompoundControlPersistence
		{

		private:
			std::string rootPath;

		private:
			void addDirContents(std::map<std::string, PresetTreeNode>& m, std::shared_ptr<moduru::file::Directory> dir);

		public:
			//std::vector<std::string> getPresets(std::weak_ptr<CompoundControl> c) override;
			std::vector<std::string> getPresets() override;
			void loadPreset(std::weak_ptr<CompoundControl> c, const std::string& name) override;
			void savePreset(std::weak_ptr<CompoundControl> c, const std::string& name) override;
			//PresetTreeNode getPresetsRecursive(std::weak_ptr<CompoundControl> c) override;
			PresetTreeNode getPresetsRecursive() override;
			void getStateAsVector(std::vector<char>& vec, std::weak_ptr<CompoundControl> c);
			void setStateFromVector(std::vector<char>& vec, std::weak_ptr<CompoundControl> c);

		private:
			smf::MidiFile* getStateAsMidiFile(std::weak_ptr<CompoundControl> c);
			smf::MidiFile* getMidiFileFromStateVec(std::vector<char>& vec);

		public:
			virtual std::string getPath(std::weak_ptr<CompoundControl> c);

		public:
			CompoundControlMidiPersistence(const std::string& rootPath);

		};
	}
}
