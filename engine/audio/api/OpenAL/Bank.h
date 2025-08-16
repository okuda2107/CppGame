#pragma once
#include <string>
#include <unordered_map>
#include <vector>

#include "alut.h"
#include "document.h"

namespace OpenAL {
// イベント，サンプルデータ，ストリーミングデータの保持を最適化
class Bank {
    std::unordered_map<std::string, class Event*> mEvents;
    std::unordered_map<std::string, ALuint> mSounds;

    bool LoadVersion1(rapidjson::Document& outDoc);

   public:
    Bank();
    ~Bank();

    bool Load(const std::string& fileName, class OpenAL::System* system);
    bool Unload();

    std::unordered_map<std::string, class Event*>& GetEvents() {
        return mEvents;
    };
};
}  // namespace OpenAL
