#ifndef KEYSTATE_COMPONENT_H_
#define KEYSTATE_COMPONENT_H_

#include <unordered_map>

#include "component.h"

class CompKeyState : public Component
{
public:
    std::unordered_map<char, bool> pressed;
    std::unordered_map<char, bool> push;
    std::unordered_map<char, bool> release;
    std::unordered_map<char, bool> held;
};

#endif  // KEYSTATE_COMPONENT_H_
