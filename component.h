#ifndef COMPONENT_H_
#define COMPONENT_H_

#include <iostream>
#include <functional>
#include <memory>
#include <type_traits>

#include "type_id.h"

// The component is a set of data typically
// owned by an entity. The types of components
// an entity has dictates what operations 
// are performed on it.
// There are also singleton components
// Not owned by any entity but are states
// and data used by certain systems
class Component
{
public:

    // Used by systems to get other components
    // owned by the entity that owns this component
    template <class SibType>
    SibType * sibling()
    {
        SibType * sib = static_cast<SibType*>(
            get_component(type_id<SibType>, _entity_id));
        return sib;
    }

    // Component initialization. 
    // The component manager hands each component
    // a helper function enabling it to find other
    // components
    void init(std::function<Component*(CompType, EntityId)>& f, EntityId eid)
    {
        get_component = f;
        _entity_id = eid;
        set_type();
    }

    virtual void set_type() { _type = type_id<Component>; }

    EntityId get_entity() { return _entity_id; }

protected:
    std::function<Component*(CompType, EntityId)> get_component;
    CompType _type;
private:
    EntityId _entity_id;
};

#endif  // COMPONENT_H_
