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
    OpenAL::Bank* bank = new OpenAL::Bank();
    bank->Load(name, this);

    // バンク内に定義されているイベントをコピー
    for (auto& event : bank->GetEvents()) {
        auto out = mEvents.emplace(event);
        if (out.second) {
            SDL_Log("Waning: Event name is duplication: %s", out.first->first);
        }
    }
}

void OpenAL::System::UnloadBank(const std::string& name) {
    auto iter = mBanks.find(name);
    if (iter == mBanks.end()) return;

    // イベントのコピーを開放
    // イベントはバンクのエベントを参照しているはずなので，イベントの実体を開放する必要はない？
    auto events = iter->second->GetEvents();
    for (auto event : events) {
        auto iter = mEvents.find(event.first);
        if (iter != mEvents.end()) {
            // delete iter->second;
            mEvents.erase(iter);
        }
    }

    // バンクの開放
    iter->second->Unload();
    delete iter->second;
    mBanks.erase(iter);
}

void OpenAL::System::UnloadAllBanks() {
    for (auto bank : mBanks) {
        bank.second->Unload();
        delete bank.second;
    }
    // for (auto event : mEvents) {
    //     delete event.second;
    // }
    mBanks.clear();
    mEvents.clear();
}

void OpenAL::System::Update(float deltaTime) {
    test();
    ;
}

void OpenAL::System::SetListener(const Matrix4& viewMatrix) {
    ;
    ;
}
