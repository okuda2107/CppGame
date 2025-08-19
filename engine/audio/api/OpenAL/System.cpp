#include "System.h"

#include "Game.h"
#include "SDL_mixer.h"
#include "al.h"
#include "alc.h"
#include "alext.h"
#include "alut.h"
#include "api/OpenAL/Bank.h"
#include "api/OpenAL/Handler.h"
#include "efx-creative.h"
#include "efx-presets.h"
#include "efx.h"

OpenAL::System::System(class Game* game) : AudioSystem(game) {}
OpenAL::System::~System() {}

bool OpenAL::System::Initialize() {
    if (!Mix_Init(MIX_INIT_MP3 || MIX_INIT_OGG)) {
        SDL_Log("Failed to Initialize SDL_Mixer");
        return false;
    }
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048)) {
        SDL_Log("Failed to open auido device");
        return false;
    }
    if (alutInit(NULL, NULL) != AL_TRUE) {
        SDL_Log("Failed to Initialize OpenAL");
        return false;
    }
    alutGetError();

    return true;
}

void OpenAL::System::Shutdown() {
    alutExit();
    Mix_CloseAudio();
    Mix_Quit();
}

void OpenAL::System::LoadBank(const std::string& name) {
    if (mBanks.find(name) != mBanks.end()) return;

    // バンクをロード
    OpenAL::Bank* bank = new OpenAL::Bank();
    if (!bank->Load(name)) {
        SDL_Log("Failed to load bank data");
        return;
    }
    mBanks.emplace(name, bank);

    // バンク内に定義されているイベントをコピー
    for (auto& event : bank->GetEvents()) {
        auto out = mEvents.emplace(event);
        if (!out.second) {
            SDL_Log("Waning: Event name is duplication: %s",
                    out.first->first.c_str());
        }
    }
}

void OpenAL::System::UnloadBank(const std::string& name) {
    auto iter = mBanks.find(name);
    if (iter == mBanks.end()) return;

    // イベントのコピーを開放
    // イベントはバンクのイベントを参照しているはずなので，イベントの実体を開放する必要はない？
    auto events = iter->second->GetEvents();
    for (auto event : events) {
        auto iter = mEvents.find(event.first);
        if (iter != mEvents.end()) {
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

    mBanks.clear();
    mEvents.clear();
}

// 再生が終了したハンドラをクリーンアップする
void OpenAL::System::Update(float deltaTime) {
    // stopしたハンドラを探す
    std::vector<unsigned int> done;
    for (auto& iter : mHandlers) {
        // ハンドラの状態を取得
        Handler* handler = iter.second;
        ALint state = handler->GetState();
    };
    ;
}

void OpenAL::System::SetListener(const Matrix4& viewMatrix) {
    ;
    ;
}

// OpenALのSourceを作成．失敗するとnullptrを返す．
SoundHandler* OpenAL::System::PlayEvent(const std::string& name) {
    auto iter = mEvents.find(name);
    if (iter != mEvents.end()) {
        // サウンドハンドラを作成
        ALuint source;
        source = iter->second->CreateSource();
        // サウンドハンドラを登録
        OpenAL::Handler* handler = new OpenAL::Handler(this, source);
        mHandlers.emplace(source, handler);
        return handler;
    } else
        return nullptr;
}
