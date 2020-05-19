#ifndef INPUT_SYSTEM_H_
#define INPUT_SYSTEM_H_

#include "keystate_component.h"

class SysInput : System
{
public:
    void update(double dt)
    {
        auto& key_state = get_array<CompKeyState>();
    }
};

#endif  // INPUT_SYSTEM_H_
