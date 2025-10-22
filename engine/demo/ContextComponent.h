#pragma once

#include "Component.h"

// 実験的に導入したものなので，demoディレクトリに配置する

// Actorが別Actorを参照したいときに用いる
// そのまま参照すると，既に削除され，ダングリングポインタになっている可能性があるので，不正アクセスを禁止する責務
template <class T>
concept ActorClass = std::is_base_of_v<Actor, T>;
template <ActorClass T>
class ContextComponent : public Component {
    T* mListenActor;  // 参照したい相手

   public:
    ContextComponent(class Actor* actor, int updateOrder = 1000)
        : Component(actor, updateOrder), mListenActor(nullptr) {}

    void Update(float deltatime) override {
        if (mListenActor && mListenActor->GetState() == Actor::State::EDead)
            mListenActor = nullptr;
    }

    void SetActor(T* actor) { mListenActor = actor; }
    T GetActor() { return mListenActor; }
};
