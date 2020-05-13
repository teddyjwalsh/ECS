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
    virtual int add(std::function<Component*(CompType, EntityId)> f) = 0; 
    virtual Component * get_component(CompIndex index) = 0;
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

    int add(std::function<Component*(CompType, EntityId)> f) override
    {
        int out_index = -1;
        if (_unused.empty())
        {
            _array.push_back(T());
            _array.back().init(f);
            out_index = _array.size() - 1;
        } 
        else
        {
            out_index = _unused.front();
            _unused.pop_front();
            _array[out_index] = T();
            _array[out_index].init(f);
        }
        return out_index;
    }

    Component * get_component(CompIndex index) override
    {
        return static_cast<Component*>(&_array[index]);
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

