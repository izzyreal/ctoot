#pragma once
#include <control/Control.hpp>

namespace ctoot::control
{
class CompoundControl
: public Control
{

public:
    static const int USE_PARENT_PROVIDER_ID{ 0 };
    
    static int deriveInstanceIndex(std::string name);
    
protected:
    std::vector<std::shared_ptr<Control>> controls;
    std::vector<std::weak_ptr<Control>> weakControls;
    
public:
    int instanceIndex = 0;
    
public:
    int providerId = USE_PARENT_PROVIDER_ID;
    
public:
    std::vector<std::string> getControlNamesRecursive(int generation = 0);
    
public:
    virtual void checkInstanceIndex(int index);
    virtual int getMaxInstance();
    virtual void add(std::shared_ptr<Control> control);
    virtual void remove(std::weak_ptr<Control> control);
    
public:
    virtual std::vector<std::weak_ptr<Control>> getControls();
    virtual std::string toString();

    virtual int getInstanceIndex();

    virtual std::weak_ptr<Control> find(std::string name);
    virtual std::weak_ptr<CompoundControl> find(int providerId, int moduleId, int instanceIndex);
    virtual std::weak_ptr<Control> deepFind(int controlId);

    virtual bool canBeInsertedBefore();

    virtual int getProviderId();
    virtual void setProviderId(int id);
    virtual void setInstanceIndex(int idx);
    
public:
    virtual void disambiguate(std::weak_ptr<CompoundControl> c);
    
public:
    virtual void close();
    
private:
    
public:
    virtual void setEnabled(bool enable) override;
    
public:
    CompoundControl(int id, int instanceIndex, std::string name);
    CompoundControl(int id, std::string name);
    virtual ~CompoundControl() override;
    
private:
    friend class ControlColumn;
    friend class ControlRow;
    friend class BypassControl;
};
}
