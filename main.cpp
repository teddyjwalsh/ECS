#include "physics_component.h"
#include "physics_system.h"
#include "component_manager.h"

int main()
{
    auto x = ComponentManager();
    x.add_array<CompPosition>();
    x.add_array<CompBounds>();
    x.add_array<CompPhysics>();

    SysPhysics ps;
    std::cout << type_id<CompPhysics> << "\n";
}
