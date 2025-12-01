#pragma once
#include <unordered_map>

#include "AL/alut.h"
#include "Math.h"

class AudioSystem {
   protected:
    class Game* mGame;

   public:
    AudioSystem(class Game* game) {};
    virtual ~AudioSystem() {};

    virtual bool Initialize() = 0;
    virtual void Shutdown() = 0;

    virtual void LoadBank(const std::string& name) = 0;
    virtual void UnloadBank(const std::string& name) = 0;
    virtual void UnloadAllBanks() = 0;

    virtual void Update(float deltaTime) = 0;

    virtual void SetListener(const Matrix4& viewMatrix) = 0;

    virtual class SoundHandler* PlayEvent(const std::string& name) = 0;
};
