#ifndef COMPONENT_ARRAY_H_
#define COMPONENT_ARRAY_H_

#include <deque>
#include <vector>

#include "component.h"


class ComponentArrayBase
{
public:
    ComponentArrayBase(CompType in_type):
        _type(in_type)
    {
    }

    //virtual int add() = 0;
    virtual int add(std::function<Component*(CompType, EntityId)> f, EntityId eid) = 0; 
    virtual EntityId remove(CompIndex index) = 0;
    virtual Component * get_component(CompIndex index) = 0;
    virtual bool empty() = 0;
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

    bool empty() override
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

