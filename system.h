#ifndef SYSTEM_H_
#define SYSTEM_H_

#include "component.h"

class System
{
public:
    virtual void update(std::shared_ptr<ComponentArrayBase> in_array, 
                double dt) = 0;
protected:
    CompType _type;
};

#endif  // SYSTEM_H_
