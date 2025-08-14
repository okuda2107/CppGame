#pragma once
#include <string>

#include "AudioSystem.h"

namespace OpenAL {
class System : public AudioSystem {
   public:
    System(class Game* game);
    ~System();

    bool Initialize() override;
    void Shutdown() override;

    void LoadBank(const std::string& name) override;
    void UnloadBank(const std::string& name) override;
    void UnloadAllBanks() override;

    void Update(float deltaTIme) override;

    void SetListener(const Matrix4& viewMatrix) override;
};
}  // namespace OpenAL
