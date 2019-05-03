#pragma once
#include <control/Control.hpp>
#include <control/CompoundControlPersistence.hpp>

using namespace std;

namespace ctoot {
	namespace control {

		class CompoundControl
			: public Control
		{

		private:
			static shared_ptr<CompoundControlPersistence> persistence;

		public:
			static weak_ptr<CompoundControlPersistence> getPersistence();
			static void setPersistence(shared_ptr<CompoundControlPersistence> p);

		public:
			static const int USE_PARENT_PROVIDER_ID{ 0 };

			static int deriveInstanceIndex(string name);

		protected:
			vector<shared_ptr<Control>> controls{};

		public:
			int instanceIndex = 0;

		public:
			int providerId = USE_PARENT_PROVIDER_ID;

		public:
			vector<string> getControlNamesRecursive(int generation);

		public:
			virtual void checkInstanceIndex(int index);
			virtual int getMaxInstance();
			virtual void add(shared_ptr<Control> control);
			virtual void remove(weak_ptr<Control> control);

		public:
			vector<weak_ptr<Control>> getMemberControls();
			virtual vector<weak_ptr<Control>> getControls();
			virtual string toString();
			virtual bool isAlwaysVertical();
			virtual bool isAlwaysHorizontal();
			virtual bool isNeverBordered();
			virtual float getAlignmentY();
			virtual string* getAlternate();
			virtual int getInstanceIndex();
			virtual weak_ptr<Control> findByTypeIdName(string typeIdName);
			virtual weak_ptr<Control> find(string name);
			virtual weak_ptr<CompoundControl> find(int providerId, int moduleId, int instanceIndex);
			virtual weak_ptr<Control> deepFind(int controlId);
			virtual bool canBeMoved();
			virtual bool canBeMovedBefore();
			virtual bool canBeInsertedBefore();
			virtual bool canBeDeleted();
			virtual bool canBeMinimized();
			virtual bool hasPresets();
			virtual bool hasCustomUI();
			virtual bool canLearn();
			virtual bool getLearn();
			virtual void setLearn(bool learn);
			virtual string getPersistenceDomain();
			virtual bool isPluginParent();
			virtual int getProviderId();
			virtual void setProviderId(int id);
			virtual void setInstanceIndex(int idx);

		public:
			virtual void disambiguate(weak_ptr<CompoundControl> c);

		public:
			virtual void close();

		private:

		public:
			virtual void setEnabled(bool enable) override;

		public:
			CompoundControl(int id, int instanceIndex, string name);
			CompoundControl(int id, string name);
			virtual ~CompoundControl();

		private:
			friend class ControlColumn;
			friend class ControlRow;
			friend class BypassControl;
		};

	}
}
