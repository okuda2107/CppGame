#include "System.h"

#include "Game.h"
#include "al.h"
#include "alc.h"
#include "alext.h"
#include "alut.h"
#include "api/OpenAL/Bank.h"
#include "efx-creative.h"
#include "efx-presets.h"
#include "efx.h"

OpenAL::System::System(class Game* game) : AudioSystem(game) {}
OpenAL::System::~System() {}

bool OpenAL::System::Initialize() {
    if (alutInit(NULL, NULL) != AL_TRUE) {
        SDL_Log("Failed to Initialize OpenAL");
        return false;
    }
    alutGetError();

    return true;
}

void OpenAL::System::Shutdown() { alutExit(); }

void OpenAL::System::LoadBank(const std::string& name) {
    if (mBanks.find(name) != mBanks.end()) return;

    // バンクをロード
    OpenAL::Bank* bank = nullptr;
    bank->Load(name);
    // バンクファイルはjsonで表現
    /* Notes:
    {

    }
     */
}

void OpenAL::System::UnloadBank(const std::string& name) {
    ;
    ;
}

void OpenAL::System::UnloadAllBanks() {
    ;
    ;
}

void OpenAL::System::Update(float deltaTime) {
    test();
    ;
}

void OpenAL::System::SetListener(const Matrix4& viewMatrix) {
    ;
    ;
}
