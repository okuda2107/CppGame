#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "SDL.h"
#include "SDL_image.h"

namespace KeyboardAndMouse {
class InputSystem;
}

class Game {
   public:
    enum GameState { EGameplay, EPaused, EQuit };

   private:
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();

    void HandleKeyPress(int key);
    void UpdateActors(float deltatime);

    void LoadData();
    void UnloadData();

    class Renderer* mRenderer;
    class AudioSystem* mAudioSystem;
    KeyboardAndMouse::InputSystem* mInputSystem;
    class PhysWorld* mPhysWorld;

    GameState mGameState;
    Uint32 mTicksCount;

    std::vector<class Actor*> mActors;
    std::vector<class Actor*> mPendingActors;
    bool mUpdatingActors;

    std::unordered_map<std::string, class Font*> mFonts;
    std::vector<class UIScreen*> mUIStack;

    // フィールドの大きさ
    // このゲームにおいて，フィールドのサイズは共通なので，Gameクラスで定義する
    class Vector2* mFieldMin;
    class Vector2* mFieldMax;

   public:
    Game();
    bool Initialize();
    void RunLoop();
    void Shutdown();

    void AddActor(class Actor* actor);
    void RemoveActor(class Actor* actor);

    class Renderer* GetRenderer() { return mRenderer; }
    class AudioSystem* GetAudioSystem() { return mAudioSystem; }
    KeyboardAndMouse::InputSystem* GetInputSystem() { return mInputSystem; }
    class PhysWorld* GetPhysWorld() { return mPhysWorld; }

    GameState GetState() const { return mGameState; }
    void SetState(GameState state) { mGameState = state; }

    class Font* GetFont(const std::string& filename);

    // Manage UI stack
    const std::vector<class UIScreen*>& GetUIStack() { return mUIStack; }
    void PushUI(class UIScreen* screen) { mUIStack.emplace_back(screen); }

    class Vector2* GetFieldMin() { return mFieldMin; }
    class Vector2* GetFieldMax() { return mFieldMax; }
};
