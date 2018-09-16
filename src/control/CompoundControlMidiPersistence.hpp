#pragma once
#include <control/CompoundControl.hpp>
#include <control/CompoundControlPersistence.hpp>

#include <file/File.hpp>

namespace ctoot {
	namespace control {
		class CompoundControlMidiPersistence
			: public virtual CompoundControlPersistence
		{

		private:
			std::string rootPath;

		public:
			std::vector<std::string> getPresets(std::weak_ptr<CompoundControl> c) override;
			void loadPreset(std::weak_ptr<CompoundControl> c, const std::string& name) override;
			void savePreset(std::weak_ptr<CompoundControl> c, const std::string& name) override;

		public:
			virtual std::string getPath(std::weak_ptr<CompoundControl> c);

		public:
			CompoundControlMidiPersistence(const std::string& rootPath);

		};
	}
}
