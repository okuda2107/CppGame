#pragma once
#include <string>
#include <unordered_map>

#include "AudioSystem.h"
#include "Helper.h"
#include "Math.h"
#include "SDL.h"
#include "alut.h"
#include "api/OpenAL/Event.h"

namespace OpenAL {
// サウンドイベントの管理
class System : public AudioSystem {
    // バンク: 複数のイベントを編集，ロード単位で管理
    std::unordered_map<std::string, class Bank*> mBanks;
    // イベント: ゲームから要請される単位で音声データとその再生情報を管理
    // 継承されているmEventsに入ってるイベントの実体はBankの中にあるイベントの参照コピーであるから注意
    std::unordered_map<std::string, class Event*> mEvents;
    // イベントインスタンス: 再生中の音声を管理
    // 再生が終了するタイミングは不明であり，アクセスがランダムであるのでunordered_map
    std::unordered_map<unsigned int, class EventInstance*> mInstances;

    friend class Handler;

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
    class SoundHandler* PlayEvent(const std::string& name) override;

    // idのインスタンスが無ければ，nullptrを返す
    class EventInstance* GetInstance(unsigned int id) {
        auto iter = mInstances.find(id);
        return iter != mInstances.end() ? iter->second : nullptr;
    };
};
}  // namespace OpenAL
