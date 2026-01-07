#pragma once
#include "game/UI/UIScreen.h"
#include "game/scene/Scene.h"

class TitleScene : public Scene {
    UIID mTitleID;

   public:
    void LoadActors();
    void UnloadActors();

    void TickRules();

    std::string PollNextScene();
};
