#include "physics_component.h"
#include "physics_system.h"
#include "time_system.h"
#include "component_manager.h"
#include "pickup_system.h"
#include "time_component.h"
#include "entity_manager.h"
#include "player_entity.h"

int main()
{
    auto c = std::make_shared<ComponentManager>();
    auto e = EntityManager();
    c->add_array<CompPosition>();
    c->add_array<CompBounds>();
    c->add_array<CompPhysics>();
    c->add_array<CompTime>();
    c->add_component<CompTime>();
    c->add_entity({type_id<CompPhysics>, type_id<CompPosition>, type_id<CompBounds>});

    SysPhysics ps;
    SysTime ts;
    std::cout << type_id<CompPhysics> << "\n";
    std::cout << type_id<CompPosition> << "\n";
    std::cout << type_id<CompBounds> << "\n";
    e.set_component_manager(c);
    Entity proto_player;
    proto_player._components[type_id<CompPosition>] = 0;
    proto_player._components[type_id<CompBounds>] = 0;
    proto_player._components[type_id<CompPhysics>] = 0;
    //e.add_entity(proto_player);
    //e.add_entity(proto_player);
    //e.add_entity(proto_player);
    for (int i = 0; i < 20; ++i)
    {
        ps.update(c->get_array(type_id<CompPhysics>), 0.1);
        ts.update(c->get_array<CompTime>(), 0.1);
    }
}
