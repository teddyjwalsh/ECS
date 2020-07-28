#ifndef HUD_COMPONENTS_H_
#define HUD_COMPONENTS_H_


struct HudElement
{
    HudObject * object;
    std::vector<HudElement*> children;

    template <class T>
    void attach(T * val)
    {
    }
};

class CompHudElement : public Component
{
    HudElement hud;
};

#endif  // HUD_COMPONENTS_H_
