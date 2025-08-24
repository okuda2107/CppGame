#include "System.h"

#include "Game.h"
#include "Math.h"
#include "SDL.h"
#include "SDL_mixer.h"
#include "al.h"
#include "alut.h"
#include "api/OpenAL/Bank.h"
#include "api/OpenAL/EventInstance.h"
#include "api/OpenAL/Handler.h"
#include "api/OpenAL/Helper.h"

OpenAL::System::System(class Game* game) : AudioSystem(game) {}
OpenAL::System::~System() {}

bool OpenAL::System::Initialize() {
    if (!Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG)) {
        SDL_Log("Failed to Initialize SDL_Mixer");
        return false;
    }
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, AUDIO_S16SYS, 1, 2048)) {
        SDL_Log("Failed to open auido device");
        return false;
    }

    // deviceのオープン
    mDevice = alcOpenDevice(NULL);
    if (!mDevice) {
        SDL_Log("Failed to open OpenAL device");
        return false;
    }

    // 音を再生する環境 (=context) の作成
    mContext = alcCreateContext(mDevice, NULL);
    if (!mContext) {
        SDL_Log("Failed to create OpenAL context");
        alcCloseDevice(mDevice);
        return false;
    }

    // 現在のスレッドにcontextをアタッチ
    if (!alcMakeContextCurrent(mContext)) {
        SDL_Log("Failed to Initialize OpenAL");
        alcDestroyContext(mContext);
        alcCloseDevice(mDevice);
        return false;
    }

    alGetError();

    return true;
}

void OpenAL::System::Shutdown() {
    alcMakeContextCurrent(NULL);
    alcDestroyContext(mContext);
    alcCloseDevice(mDevice);
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

    // イベントのコピーを解放
    // イベントはバンクのイベントを参照しているはずなので，イベントの実体を解放する必要はない？
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
    for (auto& iter : mInstances) {
        // イベントインスタンスの状態を取得
        EventInstance* event = iter.second;
        if (!event) {
            done.emplace_back(iter.first);
            continue;
        }
        ALint state = event->GetState();
        if (state == AL_STOPPED) {
            // リソースを解放してidを終了リストに追加
            delete iter.second;
            done.emplace_back(iter.first);
        }
    };
    // 終了したイベントインスタンスを連想配列から削除
    for (auto id : done) mInstances.erase(id);
}

void OpenAL::System::SetListener(const Matrix4& viewMatrix) {
    // ベクトルを得るためのビュー行列の逆行列を計算
    Matrix4 invView = viewMatrix;
    invView.Invert();

    // リスナーの座標
    Vector3 vec = VecToOpenAL(invView.GetTranslation());
    ALfloat pos[] = {vec.x, vec.y, vec.z};

    // 向いている方向
    // 逆ビューでは第3行が前方向
    Vector3 forward = VecToOpenAL(invView.GetZAxis());
    // 逆ビューでは第2行が上方向
    Vector3 up = VecToOpenAL(invView.GetYAxis());
    // {front[3], up[3]}，{前方向ベクトル (x, y, z), 上方向ベクトル (x, y,
    // z)}からなる6要素の配列
    ALfloat ori[] = {forward.x, forward.y, forward.z, up.x, up.y, up.z};

    // 速度
    ALfloat vel[] = {0, 0, 0};

    // それぞれ設定
    alListenerfv(AL_POSITION, pos);
    alListenerfv(AL_ORIENTATION, ori);
    alListenerfv(AL_VELOCITY, vel);
}

// OpenALのSourceを作成．失敗するとnullptrを返す．
SoundHandler* OpenAL::System::PlayEvent(const std::string& name) {
    auto iter = mEvents.find(name);
    if (iter != mEvents.end()) {
        // イベントインスタンスを作成，登録
        OpenAL::EventInstance* instance =
            new OpenAL::EventInstance(iter->second);
        unsigned int id = instance->GetSource();
        mInstances.emplace(id, instance);
        // サウンドハンドラを作成
        OpenAL::Handler* handler = new OpenAL::Handler(this, id);
        return handler;
    } else
        return nullptr;
}
