#ifndef COMPONENT_MANAGER_H_
#define COMPONENT_MANAGER_H_

#include <iostream>
#include <memory>
#include <vector>

#include "component_array.h"
#include "physics_component.h"
#include "type_id.h"

class ComponentManager
{
public:
    ComponentManager()
    {
    }

    template <class T>
    void add_array()
    {
        std::shared_ptr<ComponentArrayBase> new_array = std::make_shared<ComponentArray<T>>(type_id<T>);
        _arrays.push_back(new_array);
    }

    std::vector<std::shared_ptr<ComponentArrayBase>> _arrays;
private:
};

#endif  // COMPONENT_MANAGER_H_

