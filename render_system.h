#ifndef RENDER_SYSTEM_H_
#define RENDER_SYSTEM_H_

#include "ugli/general.h"
#include "system.h"
#include "component_array.h"

class SysRender : public System
{
public:
    void update(double dt) override
    {
        std::vector<CompTime>& array = get_array<CompHud>();
        for (auto& hc : array)
        {
            for (auto& he : hc.elements)
            {
                graphics::draw_hud_object(he);
            }
        }
    }
};

#endif  // RENDER_SYSTEM_H_
