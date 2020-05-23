#ifndef RAYTRACING_SYSTEM_H_
#define RAYTRACING_SYSTEM_H_

#include <memory>

#include "graphics/raytracer.h"
#include "terrain_system.h"

// The physics system is intended to simulate physics
// and collision between all entities with a physics
// Component. 
// It also currently is intended to apply player input
// to player entities
class SysRaytrace : public System
{
public:
    SysRaytrace()
    {
        _type_name = "Raytracer";
        _rt = std::make_shared<graphics::Raytracer>
            (x_chunk_size, y_chunk_size, z_chunk_size, x_res, y_res,
                x_map_size, y_map_size, z_map_size,
                low_res_div);
    }

    void update(double dt) override
    {
        auto& cam = get_array<CompCamera>()[0];
        
        _rt->draw(x_res / low_res_div, y_res / low_res_div, 5, false, false);
        _rt->draw(x_res, y_res, 1, true, true);
        _rt->set_camera(cam);
    }

private:
    std::shared_ptr<graphics::Raytracer> _rt;
    int x_chunk_size = CHUNK_SIZE_X;
    int y_chunk_size = CHUNK_SIZE_Y;
    int z_chunk_size = CHUNK_SIZE_Z;
    int x_map_size = MAP_SIZE_X;
    int y_map_size = MAP_SIZE_Y;
    int z_map_size = MAP_SIZE_Z;
    float low_res_div = 6;
    int x_res = 1024;
    int y_res = 768;

};

#endif  // RAYTRACING_SYSTEM_H_
