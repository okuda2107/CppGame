#pragma once
#include "BonfireSceneBase.h"
#include "game/UI/UIScreen.h"

class TitleScene : public BonfireSceneBase {
    UIID mTitleID;

   public:
    void LoadActors();
    void UnloadActors();

    void TickRules();

    std::string PollNextScene();
};
