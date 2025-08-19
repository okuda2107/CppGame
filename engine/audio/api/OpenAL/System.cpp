#include "System.h"

#include "Game.h"
#include "Math.h"
#include "SDL_mixer.h"
#include "al.h"
#include "alut.h"
#include "api/OpenAL/Bank.h"
#include "api/OpenAL/Handler.h"
#include "api/OpenAL/Helper.h"

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
        if (state == AL_STOPPED) {
            // リソースを解放してidを終了リストに追加
            alDeleteSources(1, &handler->mSource);
            done.emplace_back(iter.first);
        }
    };
    // 終了したイベントインスタンを連想配列から削除
    for (auto id : done) mHandlers.erase(id);
}

void OpenAL::System::SetListener(const Matrix4& viewMatrix) {
    // ベクトルを得るためのビュー行列の逆行列を計算
    Matrix4 invView = viewMatrix;
    invView.Invert();

    // リスナーの座標
    ALfloat pos[] = VecToOpenAL(invView.GetTranslation());

    // 向いている方向
    // 逆ビューでは第3行が前方向
    Vector3 forward = VecToOpenAL(invView.GetZAxis());
    // 逆ビューでは第2行が上方向
    Vector3 up = VecToOpenAL(invView.GetYAxis());
    // {front[3], up[3]}，{前方向ベクトル (x, y, z), 上方向ベクトル (x, y,
    // z)}からなる6要素の配列
    ALfloat ori[] = {forward, up};

    // 速度
    ALfloat vel[3] = {0, 0, 0};

    alListenerfv(AL_POSITION, pos);
    alListenerfv(AL_ORIENTATION, ori);
    alListenerfv(AL_VELOCITY, vel);
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
