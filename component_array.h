#ifndef COMPONENT_ARRAY_H_
#define COMPONENT_ARRAY_H_

#include <deque>
#include <vector>

#include "component.h"


// ComponentArrays are the primary storage and access 
// containers for components. They currently use contiguous memory
// and are intended to provide quick access and iteration to 
// systems

// Base class to allow common usage of template derivatives
class ComponentArrayBase
{
public:
    ComponentArrayBase(CompType in_type):
        _type(in_type)
    {
    }

    // The add function adds a component to entity with id eid.
    // It is also passed a function that components use to access 
    // siblings.
    virtual int add(std::function<Component*(CompType, EntityId)> get_component_func, EntityId eid) = 0; 

    // Remove a component of a certain index from the array
    virtual EntityId remove(CompIndex index) = 0;

    // Return a pointer to a component of a certain index
    virtual Component * get_component(CompIndex index) = 0;

    // Checks whether the array is empty
    virtual bool empty() const = 0;
protected:

    CompType _type;
};

template <class T>
class ComponentArray : public ComponentArrayBase
{
public:
    ComponentArray(CompType in_type):
        ComponentArrayBase(in_type)
    {
    }

    int add(std::function<Component*(CompType, EntityId)> f, EntityId eid) override
    {
        int out_index = -1;
        if (_unused.empty())
        {
            _array.push_back(T());
            _array.back().init(f, eid);
            out_index = _array.size() - 1;
        } 
        else
        {
            out_index = _unused.front();
            _unused.pop_front();
            _array[out_index] = T();
            _array[out_index].init(f, eid);
        }
        return out_index;
    }

    int add(std::function<Component*(CompType, EntityId)> f, EntityId eid, T proto)
    {
        int out_index = -1;
        if (_unused.empty())
        {
            _array.push_back(proto);
            _array.back().init(f, eid);
            out_index = _array.size() - 1;
        } 
        else
        {
            out_index = _unused.front();
            _unused.pop_front();
            _array[out_index] = proto;
            _array[out_index].init(f, eid);
        }
        return out_index;
    }

    EntityId remove(CompIndex index) override
    {
        _array[index] = _array[_array.size() - 1];
        _array.resize(_array.size() - 1);
        return _array[index].get_entity();
    }

    Component * get_component(CompIndex index) override
    {
        if (_array.size() >= index)
        {
            return static_cast<Component*>(&_array[index]);
        }
        else
        {
            return nullptr;
        }
    }

    bool empty() const override
    {
        return _array.empty();
    }

    std::vector<T> _array;
    std::deque<int> _unused;
};

template <class Derived>
std::shared_ptr<ComponentArray<Derived>> get_derived(std::shared_ptr<ComponentArrayBase> in_array)
{
    return std::dynamic_pointer_cast<ComponentArray<Derived>>(in_array);
}

#endif  // COMPONENT_ARRAY_H_

