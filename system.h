#ifndef SYSTEM_H_
#define SYSTEM_H_

#include <string>

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

    std::string& get_type_name()
    {
        return _type_name;
    }

protected:
    CompType _type;
    std::string _type_name = "default";
    std::function<ComponentArrayBase*(CompType)> get_array_base;
};

#endif  // SYSTEM_H_
