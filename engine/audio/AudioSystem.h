#pragma once
#include <unordered_map>

#include "Math.h"
#include "alut.h"

template <typename BankType, typename EventType>
class AudioSystem {
   protected:
    class Game* mGame;

    // バンク: 複数のイベントを編集，ロード単位で管理
    std::unordered_map<std::string, BankType*> mBanks;
    // イベント: ゲームから要請される単位で音声データとその再生情報を管理
    std::unordered_map<std::string, EventType*> mEvents;
    // ハンドラ: 再生中の音声を管理
    // 再生が終了するタイミングは不明であり，アクセスがランダムであるのでunordered_map
    std::unordered_map<unsigned int, class SoundHandler*> mHandlers;

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

    std::unordered_map<unsigned int, class SoundHandler*>& GetHandlers() {
        return mHandlers;
    };

    virtual class SoundHandler* PlayEvent(const std::string& name) = 0;

    virtual void loadtest() {

    };

    virtual void unloadtest() {};
};

// 現在使っているサウンドエンジン
#include "api/OpenAL/Bank.h"
#include "api/OpenAL/Event.h"

typedef AudioSystem<OpenAL::Bank, OpenAL::Event> Audio;
