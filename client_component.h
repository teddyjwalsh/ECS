#ifndef CLIENT_COMPONENT_H_
#define CLIENT_COMPONENT_H_

#include "component.h"
#include "type_id.h"

class CompClient : public Component
{
public:
    EntityId player_id;
};

#endif  // CLIENT_COMPONENT_H_
