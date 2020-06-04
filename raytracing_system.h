#ifndef RAYTRACING_SYSTEM_H_
#define RAYTRACING_SYSTEM_H_

#include <memory>

#include "raytracer.h"
#include "terrain_system.h"
#include "graphics_component.h"

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
        graphics::init(x_res, y_res);
        _type_name = "Raytracer";
        _rt = std::make_shared<graphics::Raytracer>
            (x_chunk_size, y_chunk_size, z_chunk_size, x_res, y_res,
                x_map_size, y_map_size, z_map_size,
                low_res_div);
    }

    void init_update() override
    {
        auto& cam = get_array<CompCamera>()[0];
        auto& cg = get_array<CompGraphics>()[0];
        cg.window = graphics::window;
        auto pos = cam.sibling<CompPosition>();
        _rt->set_ref(pos->pos);
        _rt->set_camera(&cam.camera);
        _rt->set_textures({ "images/grass.bmp", "images/grass_top.bmp", "images/grass_bottom.bmp",
                       "images/stone.bmp", "images/stone.bmp", "images/stone.bmp",
                        "images/grass_bottom.bmp", "images/grass_bottom.bmp", "images/grass_bottom.bmp",
                        "images/sand.bmp", "images/sand.bmp", "images/sand.bmp" });

        auto& chunk_data_queue = get_array<CompChunkDataQueue>()[0];

        while (!chunk_data_queue.chunks.empty())
        {
            auto new_chunk = chunk_data_queue.chunks.front();
            chunk_data_queue.chunks.pop_front();
            _rt->add_chunk(new_chunk.coord.x*CHUNK_SIZE_X, new_chunk.coord.y*CHUNK_SIZE_Y, new_chunk.coord.z*CHUNK_SIZE_Z, new_chunk.data);
        }
    }

    void update(double dt) override
    {
        auto& cam = get_array<CompCamera>()[0];
        auto pos = cam.sibling<CompPosition>();
        _rt->set_ref(pos->pos);
        _rt->draw(x_res / low_res_div, y_res / low_res_div, 5, false, false);
        _rt->draw(x_res, y_res, 1, true, true);
        cam.camera.set_pos(pos->pos);
        _rt->set_camera(&cam.camera);

        auto& chunk_data_queue = get_array<CompChunkDataQueue>()[0];
        if (!chunk_data_queue.chunks.empty())
        {
            auto new_chunk = chunk_data_queue.chunks.front();
            chunk_data_queue.chunks.pop_front();
            _rt->add_chunk(new_chunk.coord.x, new_chunk.coord.y, new_chunk.coord.z, new_chunk.data);
        }
    }

private:
    std::shared_ptr<graphics::Raytracer> _rt;
    int x_chunk_size = CHUNK_SIZE_X;
    int y_chunk_size = CHUNK_SIZE_Y;
    int z_chunk_size = CHUNK_SIZE_Z;
    int x_map_size = MAP_SIZE_X;
    int y_map_size = MAP_SIZE_Y;
    int z_map_size = MAP_SIZE_Z;
    float low_res_div = 4;
    int x_res = 1024;
    int y_res = 768;

};

#endif  // RAYTRACING_SYSTEM_H_
