#pragma once

#include "Actor.h"
#include "Game.h"
#include "Mesh.h"
#include "RenderPath.h"
#include "Renderer.h"

class PostEffectTestActor : public Actor {
   public:
    PostEffectTestActor(class Game* game) : Actor(game) {
        // 空間感を出すためのオブジェクト配置
        Actor* cube = new Actor(GetGame());
        cube->SetPosition(Vector3(100, -50, 0));
        cube->SetScale(25.0);
        std::string effectName = "Shaders/PostEffectBlur";
        auto rp = game->GetRenderer()->GetRenderPath(effectName);
        rp->AddEffect(game->GetRenderer()->GetShader(effectName));
        RenderConfig cube_config = RenderConfig();
        cube_config.effectName = effectName;
        MeshComponent* cube_mc = new MeshComponent(cube, cube_config);
        cube_mc->SetMesh(
            GetGame()->GetRenderer()->GetMesh("Assets/Cube.gpmesh"));

        Actor* sphere = new Actor(GetGame());
        sphere->SetPosition(Vector3(100, 50, 0));
        RenderConfig sphere_config = RenderConfig();
        MeshComponent* sphere_mc = new MeshComponent(sphere, cube_config);
        sphere_mc->SetMesh(
            GetGame()->GetRenderer()->GetMesh("Assets/Sphere.gpmesh"));
    }
};
