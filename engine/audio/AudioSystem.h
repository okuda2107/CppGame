#pragma once
#include <unordered_map>

#include "Math.h"
#include "alut.h"

class AudioSystem {
   protected:
    class Game* mGame;

   public:
    AudioSystem(class Game* game) {};
    virtual ~AudioSystem() {};

    virtual bool Initialize() = 0;
    virtual void Shutdown() {};

    virtual void LoadBank(const std::string& name) {};
    virtual void UnloadBank(const std::string& name) {};
    virtual void UnloadAllBanks() {};

    virtual void Update(float deltaTime) {};

    virtual void SetListener(const Matrix4& viewMatrix) {};

    virtual class SoundHandler* PlayEvent(const std::string& name) = 0;

    virtual void loadtest() {

    };

    virtual void unloadtest() {};
};
