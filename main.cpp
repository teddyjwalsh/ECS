#include "physics_component.h"
#include "physics_system.h"
#include "time_system.h"
#include "component_manager.h"
#include "pickup_system.h"
#include "octree_system.h"
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
    c->add_array<CompOctree>();
    c->add_array<CompOctreeRoot>();
    c->add_component<CompTime>();
    c->add_component<CompOctreeRoot>();
    EntityId player = c->add_entity({type_id<CompPhysics>, 
                   type_id<CompPosition>, 
                   type_id<CompBounds>,  
                   type_id<CompOctree>});
    c->set_entity_pos(player, glm::vec3(0,10,0));

    EntityId player2 = c->add_entity({type_id<CompPhysics>, 
                   type_id<CompPosition>, 
                   type_id<CompBounds>,  
                   type_id<CompOctree>});
    c->set_entity_pos(player2, glm::vec3(10,20,0));

    auto ps = std::make_shared<SysPhysics>();
    auto ts = std::make_shared<SysTime>();
    auto os = std::make_shared<SysOctree>();
    std::cout << type_id<CompPhysics> << "\n";
    std::cout << type_id<CompPosition> << "\n";
    std::cout << type_id<CompBounds> << "\n";
    //e.add_entity(proto_player);
    //e.add_entity(proto_player);
    //e.add_entity(proto_player);
    c->add_system(ps);
    c->add_system(ts);
    c->add_system(os);
    for (int i = 0; i < 20; ++i)
    {
        c->update();
    }
}
