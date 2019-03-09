#pragma once

#include <string>
#include <vector>
#include <memory>

namespace ctoot {
	namespace control {

		class CompoundControl;

		struct PresetTreeNode {
			std::map<std::string, PresetTreeNode> node;
			bool directory = false;
			std::string parentPath = "";
		};

		class CompoundControlPersistence
		{
		public:
			//virtual std::vector<std::string> getPresets(std::weak_ptr<CompoundControl> c) = 0;
			virtual std::vector<std::string> getPresets() = 0;
			virtual void loadPreset(std::weak_ptr<CompoundControl> c, const std::string& name) = 0;
			virtual void savePreset(std::weak_ptr<CompoundControl> c, const std::string& name) = 0;
			//virtual PresetTreeNode getPresetsRecursive(std::weak_ptr<CompoundControl> c) = 0;
			virtual PresetTreeNode getPresetsRecursive() = 0;

		};

	}
}
