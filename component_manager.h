#ifndef COMPONENT_MANAGER_H_
#define COMPONENT_MANAGER_H_

#include <iostream>
#include <memory>
#include <unordered_map>

#include "system.h"
#include "component_array.h"
#include "time_component.h"
#include "entity.h"
#include "physics_component.h"
#include "type_id.h"

class ComponentManager
{
public:
    ComponentManager():
        _entity_counter(0)
    {
        get_component = std::bind(&ComponentManager::get_entity_component,
                                  this, std::placeholders::_1, std::placeholders::_2);
        get_array_func = std::bind(&ComponentManager::get_array_p,
                                  this, std::placeholders::_1);
        
        // Temporary entity creation
    }

    template <class T>
    void add_array()
    {
        std::shared_ptr<ComponentArrayBase> new_array = 
            std::make_shared<ComponentArray<T>>(type_id<T>);
        _arrays[type_id<T>] = new_array;
    }

    CompIndex add_component(CompType in_type)
    {
        assert(!_arrays.empty());

        return _arrays[in_type]->add(get_component);
    }

    template <class ComponentType>
    CompIndex add_component()
    {
        assert(!_arrays.empty());

        return _arrays[type_id<ComponentType>]->add(get_component);
    }

    template <class ComponentType>
    CompIndex add_component(ComponentType proto)
    {
        assert(!_arrays.empty());

        return _arrays[type_id<ComponentType>]->add(get_component, proto);
    }

    EntityId add_entity(std::vector<CompType> in_types)
    {
        EntityId out_id = _entity_counter;
        _entities[out_id] = Entity();
        for (auto it : in_types)
        {
            _entities[out_id]._components[it] = add_component(it);
        }
        _entity_counter += 1;
        return out_id; 
    }

    void add_system(std::shared_ptr<System> in_system)
    {
        _systems.push_back(in_system);
        _systems.back()->pre_init(get_array_func);
    }

    ComponentArrayBase * get_array_p(CompType in_type)
    {
        assert(!_arrays.empty());

        return _arrays[in_type].get(); 
    }

    std::shared_ptr<ComponentArrayBase> get_array(CompType in_type)
    {
        assert(!_arrays.empty());

        return _arrays[in_type]; 
    }

    template <class ArrayType>
    std::shared_ptr<ComponentArrayBase> get_array()
    {
        assert(!_arrays.empty());

        return _arrays[type_id<ArrayType>]; 
    }

    Component * get_entity_component(CompType type, EntityId id)
    {
        assert(!_entities.empty());
        if (_singletons.find(type) != _singletons.end())
        {
            return _singletons[type];
        }
        CompIndex ind = _entities[id]._components[type];
        return _arrays[type]->get_component(ind);
    }

    void update()
    {
        auto ta = std::dynamic_pointer_cast<ComponentArray<CompTime>>(_arrays[type_id<CompTime>]);
        for (auto& sys : _systems)
        {
            sys->update(0.1);
        }        
    }

    std::unordered_map<CompType, std::shared_ptr<ComponentArrayBase>> _arrays;
private:
    std::function<Component*(CompType, EntityId)> get_component;
    std::function<ComponentArrayBase*(CompType)> get_array_func;
    std::unordered_map<EntityId, Entity> _entities;
    std::unordered_map<CompType, Component*> _singletons;
    std::vector<std::shared_ptr<System>> _systems;
    EntityId _entity_counter;
};

#endif  // COMPONENT_MANAGER_H_

