#pragma once

#include "game/object/Actor.h"

struct WoodDeps {
    class RenderDB& renderDB;
    class PhysWorld& physWorld;

    WoodDeps(class RenderDB& render, class PhysWorld& phys)
        : renderDB(render), physWorld(phys) {}
};

class Wood : public Actor {
    float mTime;

   public:
    Wood(class ActorsSystem* system, WoodDeps deps);
    ~Wood() = default;

    void UpdateActor(float deltatime) override;

    static constexpr std::string_view SWoodPhysTag = "wood";
};
