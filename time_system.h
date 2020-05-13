#ifndef TIME_SYSTEM_H_
#define TIME_SYSTEM_H_

#include "system.h"
#include "component_array.h"
#include "time_component.h"

class SysTime : public System
{
public:
    void update(std::shared_ptr<ComponentArrayBase> in_array, 
                double dt) override
    {
        auto array = get_derived<CompTime>(in_array);
        CompTime& time_comp = array->_array[0];
        time_comp.current_time += dt;
        std::cout << "Time: " << time_comp.current_time << "\n";
    }
};

#endif  // TIME_SYSTEM_H_
