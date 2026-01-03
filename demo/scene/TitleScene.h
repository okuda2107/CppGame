#pragma once
#include "game/scene/Scene.h"

class TitleScene : public Scene {
    UIID mTitleID;

   public:
    TitleScene(struct SceneCreateDeps& scd)
        : Scene(scd), mIsTitleFinished(false) {}

    bool mIsTitleFinished;

    void LoadActors();

    std::string PollNextScene();
};
