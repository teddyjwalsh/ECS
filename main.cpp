#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE

#include "spdlog/spdlog.h"

#include "physics_component.h"
#include "physics_system.h"
#include "time_system.h"
#include "component_manager.h"
#include "pickup_system.h"
#include "octree_system.h"
#include "terrain_system.h"
#include "input_system.h"
#include "time_component.h"
#include "client_component.h"
#include "entity_manager.h"
#include "player_entity.h"


int main()
{
    spdlog::set_level(spdlog::level::trace);
    auto c = std::make_shared<ComponentManager>();
    auto e = EntityManager();
    c->add_array<CompPosition>();
    c->add_array<CompBounds>();
    c->add_array<CompPhysics>();
    c->add_array<CompTime>();
    c->add_array<CompCamera>();
    c->add_array<CompClient>();
    c->add_array<CompPlayer>();
    c->add_array<CompLoadedChunks>();
    c->add_array<CompChunkDataQueue>();
    c->add_array<CompOctree>();
    c->add_array<CompPlayerTerrain>();
    c->add_array<CompOctreeRoot>();
    c->add_array<CompKeyState>();
    c->add_array<CompGraphics>();
    c->add_array<CompPickupper>();
    c->add_array<CompPickupee>();
    c->add_component<CompTime>();
    c->add_component<CompOctreeRoot>();
    c->add_component<CompLoadedChunks>();
    c->add_component<CompChunkDataQueue>();
    c->add_component<CompKeyState>();
    c->add_component<CompGraphics>();
    EntityId player = c->add_entity({type_id<CompPhysics>, 
                   type_id<CompPosition>, 
                   type_id<CompBounds>,  
                   type_id<CompClient>,  
                   type_id<CompPlayer>,  
                   type_id<CompCamera>,  
                   type_id<CompPickupper>,  
                   type_id<CompPlayerTerrain>,  
                   type_id<CompOctree>});
    c->set_entity_pos(player, glm::vec3(0,10,0));

    EntityId player2 = c->add_entity({type_id<CompPhysics>, 
                   type_id<CompPosition>, 
                   type_id<CompBounds>,  
                   type_id<CompOctree>});
    c->set_entity_pos(player2, glm::vec3(10,20,0));

    auto ps = std::make_shared<SysPhysics>();
    auto ts = std::make_shared<SysTime>();
    auto trs = std::make_shared<SysTerrain>();
    auto os = std::make_shared<SysOctree>();
    auto is = std::make_shared<SysInput>();
    auto pus = std::make_shared<SysPickup>();
    std::cout << type_id<CompPhysics> << "\n";
    std::cout << type_id<CompPosition> << "\n";
    std::cout << type_id<CompBounds> << "\n";
    //e.add_entity(proto_player);
    //e.add_entity(proto_player);
    //e.add_entity(proto_player);
    c->add_system(ps);
    c->add_system(ts);
    c->add_system(trs);
    c->add_system(os);
    c->add_system(is);
    c->add_system(pus);
    for (int i = 0; i < 200; ++i)
    {
        c->update();
    }
}
