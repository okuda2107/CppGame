#pragma once
#include <string>
#include <unordered_map>

#include "SoundBank.h"
#include "alut.h"

namespace OpenAL {
// イベント，サンプルデータ，ストリーミングデータの保持を最適化
class Bank : public SoundBank {
    std::unordered_map<std::string, class Event*> mEvents;
    std::unordered_map<std::string, ALuint> mSounds;

   public:
    Bank();
    ~Bank();

    bool Load(const std::string& name);
};
}  // namespace OpenAL
