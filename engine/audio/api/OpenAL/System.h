#pragma once
#include <string>

#include "AudioSystem.h"
#include "SDL.h"
#include "api/OpenAL/Bank.h"
#include "api/OpenAL/Event.h"

namespace OpenAL {
class System : public AudioSystem<Bank, Event> {
    // 継承されているmEventsに入ってるイベントの実体はBankの中にあるイベントの参照コピーであるから注意
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
    SoundHandler* PlayEvent(const std::string& name) override;

    void loadtest() {
        using namespace std;
        cout << "mBanksNum: " << mBanks.size() << endl;
        cout << "mBanksContents:" << endl;
        for (auto bank : mBanks)
            cout << bank.first << ":" << bank.second << endl;
        cout << endl;
        auto bank = mBanks.at("./Assets/Bank.json");
        cout << "eventNum in bank: " << bank->GetEvents().size() << endl;
        cout << "mEventsNum:" << mEvents.size() << endl;
        cout << "mEventsContents:" << endl;
        for (auto event : mEvents)
            cout << event.first << ":" << event.second << endl;
        cout << endl;
        SDL_Delay(3000);
    };

    void unloadtest() {
        using namespace std;
        cout << "mBanksNum: " << mBanks.size() << endl;
        cout << "mBanksContents:" << endl;
        for (auto bank : mBanks)
            cout << bank.first << ":" << bank.second << endl;
        cout << endl;
        cout << "mEventsNum:" << mEvents.size() << endl;
        cout << "mEventsContents:" << endl;
        for (auto event : mEvents)
            cout << event.first << ":" << event.second << endl;
        cout << endl;
    }
};
}  // namespace OpenAL
