#ifndef TIME_SYSTEM_H_
#define TIME_SYSTEM_H_

#include "system.h"
#include "component_array.h"
#include "time_component.h"

class SysTime : public System
{
public:
    void update(double dt) override
    {
        std::vector<CompTime>& array = get_array<CompTime>();
        CompTime& time_comp = array[0];
        time_comp.current_time += dt;
        std::cout << "TIME " << time_comp.current_time << "\n";
    }
};

#endif  // TIME_SYSTEM_H_
