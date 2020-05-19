#ifndef COMPONENT_H_
#define COMPONENT_H_

#include <iostream>
#include <functional>
#include <memory>
#include <type_traits>

#include "type_id.h"

class Component
{
public:

    template <class SibType>
    SibType * sibling()
    {
        SibType * sib = static_cast<SibType*>(
            get_component(type_id<SibType>, _entity_id));
        return sib;
    } 

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
