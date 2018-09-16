#pragma once

#include <string>
#include <vector>
#include <memory>

namespace ctoot {
	namespace control {

		class CompoundControl;

		class CompoundControlPersistence
		{
		public:
			virtual std::vector<std::string> getPresets(std::weak_ptr<CompoundControl> c) = 0;
			virtual void loadPreset(std::weak_ptr<CompoundControl> c, const std::string& name) = 0;
			virtual void savePreset(std::weak_ptr<CompoundControl> c, const std::string& name) = 0;

		};

	}
}
