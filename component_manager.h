#ifndef COMPONENT_MANAGER_H_
#define COMPONENT_MANAGER_H_

#include <iostream>
#include <memory>
#include <unordered_map>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

#include "system.h"
#include "component_array.h"
#include "time_component.h"
#include "entity.h"
#include "physics_component.h"
#include "type_id.h"

#define SLOG_TRACE(...) SPDLOG_LOGGER_TRACE(&logger, __VA_ARGS__)
#define SLOG_DEBUG(...) SPDLOG_LOGGER_DEBUG(&logger, __VA_ARGS__)
#define SLOG_ERROR(...) SPDLOG_LOGGER_ERROR(&logger, __VA_ARGS__)
#define SLOG_WARN(...) SPDLOG_LOGGER_WARN(&logger, __VA_ARGS__)
#define SLOG_CRITICAL(...) SPDLOG_LOGGER_CRITICAL(&logger, __VA_ARGS__)
#define SLOG_INFO(...) SPDLOG_LOGGER_INFO(&logger, __VA_ARGS__)

// The Component Manager 
// despite the name, manages Components
// Entities and Systems. It manages
// Creation and destruction of all these things
// As well as does the main update call.
class ComponentManager
{
public:
    
    // Engine user currently needs to create this.
    // No construction config currently required
    ComponentManager():
        logger("manager_log",{}),
        _entity_counter(0)
    {
        get_component = std::bind(&ComponentManager::get_entity_component,
                                  this, std::placeholders::_1, std::placeholders::_2);
        get_array_func = std::bind(&ComponentManager::get_array_p,
                                  this, std::placeholders::_1);

        // Log init
        _console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        _console_sink->set_level(spdlog::level::info);
        _console_sink->set_pattern("[manager] [%^%l%$] %v");

        _file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/manager.txt", true);
        _file_sink->set_level(spdlog::level::trace);

        logger = spdlog::logger(std::string("manager_log"), {_file_sink, _console_sink});
        logger.set_level(spdlog::level::trace);
    }

    // Add array currently allocates a ComponentArray
    // For the manager to use
    template <class T>
    void add_array()
    {
        std::shared_ptr<ComponentArrayBase> new_array = 
            std::make_shared<ComponentArray<T>>(type_id<T>);
        _arrays[type_id<T>] = new_array;
    }


    // All add component functions add a component
    // to the array of the given type. Arrays need to be added
    // using add_array first
    CompIndex add_component(CompType in_type, EntityId eid=-1)
    {
        assert(!_arrays.empty());

        return _arrays.at(in_type)->add(get_component, eid);
    }

    template <class ComponentType>
    CompIndex add_component(EntityId eid=-1)
    {
        assert(!_arrays.empty());

        return _arrays.at(type_id<ComponentType>)->add(get_component, eid);
    }

    template <class ComponentType>
    CompIndex add_component(ComponentType proto, EntityId eid=-1)
    {
        assert(!_arrays.empty());

        return _arrays.at(type_id<ComponentType>)->add(get_component, eid, proto);
    }

    void delete_entity(EntityId entity)
    {
        for (auto& it : _entities[entity]._components)
        {
            EntityId new_ent = _arrays[it.first]->remove(it.second);
            _entities[new_ent]._components[it.first] = it.second;
        }
    }

    // Adds an entity to the manager.
    // Entities are currently, for the most part
    // just numbers that have associations with components
    EntityId add_entity(std::vector<CompType> in_types)
    {
        EntityId out_id = _entity_counter;
        _entities[out_id] = Entity();
        for (auto it : in_types)
        {
            _entities[out_id]._components[it] = add_component(it, out_id);
        }
        _entity_counter += 1;
        SLOG_INFO("Added Entity ", out_id);            
        return out_id; 
    }

    // Adds a system to the manager. Once added, the system will update 
    // at every manager update call
    void add_system(std::shared_ptr<System> in_system)
    {
        SLOG_INFO("Adding system ", in_system->get_type_name());            
        _systems.push_back(in_system);
        _systems.back()->_pre_init(get_array_func);
        _systems.back()->_set_log_sinks({_file_sink});
    }

    ComponentArrayBase * get_array_p(CompType in_type)
    {
        assert(!_arrays.empty());

        return _arrays[in_type].get(); 
    }

    // A system helper function. Gets passed to 
    // systems so they can iterate every component o
    // of a certain type.
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

    template <class CompType>
    CompType * entity_component(EntityId entity)
    {
        return dynamic_cast<CompType*>(
            get_entity_component(type_id<CompType>, entity));
    }

    void set_entity_pos(EntityId entity, glm::vec3 in_pos)
    {
        CompPosition * pos_c = entity_component<CompPosition>(entity);    
        pos_c->pos = in_pos;
    }

    void init_update()
    {
        for (auto& sys : _systems)
        {
            SLOG_TRACE("Entering system {}", "test");//sys->get_type_name());            
            sys->init_update();
            SLOG_TRACE("Exiting system {}", sys->get_type_name());
        }
    }

    // Update all systems
    void update()
    {
        auto ta = std::dynamic_pointer_cast<ComponentArray<CompTime>>(_arrays[type_id<CompTime>]);
        for (auto& sys : _systems)
        {
            SLOG_TRACE("Entering system {}", "test");//sys->get_type_name());            
            sys->update(0.016);
            SLOG_TRACE("Exiting system {}", sys->get_type_name());            
        }        
    }

    std::unordered_map<CompType, std::shared_ptr<ComponentArrayBase>> _arrays;
private:
    std::function<Component*(CompType, EntityId)> get_component;
    std::function<ComponentArrayBase*(CompType)> get_array_func;
    std::unordered_map<EntityId, Entity> _entities;
    std::unordered_map<CompType, Component*> _singletons;
    std::vector<std::shared_ptr<System>> _systems;
    std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> _console_sink;
    std::shared_ptr<spdlog::sinks::basic_file_sink_mt> _file_sink;
    EntityId _entity_counter;
    spdlog::logger logger;
};

#endif  // COMPONENT_MANAGER_H_

