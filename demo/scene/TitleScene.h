#pragma once
#include "game/scene/Scene.h"

class TitleScene : public Scene {
   public:
    TitleScene(struct SceneCreateDeps& scd) : Scene(scd) {}

    void LoadActors();

    std::string PollNextScene();
};
