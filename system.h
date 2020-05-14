#ifndef SYSTEM_H_
#define SYSTEM_H_

#include "component.h"
#include "component_array.h"

class System
{
public:
    virtual void update(double dt) = 0;

    void pre_init(std::function<ComponentArrayBase*(CompType)> f)
    {
        get_array_base = f;
    }

    CompType get_type() const
    {
        return _type;
    }

    template <class CompType>
    std::vector<CompType>& get_array()
    {
        return dynamic_cast<ComponentArray<CompType>*>(get_array_base(type_id<CompType>))->_array;
    } 

protected:
    CompType _type;
    std::function<ComponentArrayBase*(CompType)> get_array_base;
};

#endif  // SYSTEM_H_
