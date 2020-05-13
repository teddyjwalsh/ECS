#ifndef TIME_COMPONENT_H_
#define TIME_COMPONENT_H_

#include "component.h"


class CompTime : public Component
{
public:
    double current_time = 0.0;
    
private:
    void set_type() override { _type = type_id<CompTime>; }
};

#endif  // TIME_COMPONENT_H_
