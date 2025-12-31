#pragma once
#include <map>
#include <string>
#include <type_traits>

#include "Actor.h"
#include "base/ObjectsSystemBase.h"
#include "input/InputState.h"

// 入力を処理するハンドラ
struct ProcessInputHandlerBase {
    virtual ~ProcessInputHandlerBase() = default;
    virtual void operator()(class Actor* actor, const InputState& state) {
        actor->ProcessInput(state);
    }
};

// 更新を処理するハンドラ
struct UpdateHandlerBase {
    virtual ~UpdateHandlerBase() = default;
    virtual void operator()(class Actor* actor, float deltatime) {
        actor->Update(deltatime);
    }
};

// それぞれのハンドラを束ねる構造体
struct ActorExecutionPolicy {
    ProcessInputHandlerBase* input;
    UpdateHandlerBase* update;
};

// Actorの配列を保持し，それらのupdateを保証する
class ActorsSystem : public ObjectsSystemBase<class InputState> {
    std::map<std::string, std::vector<class Actor*>> mActors;
    std::map<std::string, std::vector<class Actor*>> mPendingActors;

    // タグ別にハンドラを管理する
    // todo: ActorExecutionPolicy* は smart pointer を使った方が良いらしい．
    std::unordered_map<std::string, ActorExecutionPolicy*> mExecution;

    bool mUpdatingActors;

    void UnloadObjects() override;

   public:
    ActorsSystem();
    ~ActorsSystem() override;

    void ProcessInput(const InputState& state);
    void UpdateObjects(float deltatime);

    void AddActor(const std::string& tag, class Actor* actor);
    void RemoveActor(const std::string& tag, class Actor* actor);

    void DeleteActorsByTag(const std::string& tag);

    template <typename InputHandler, typename UpdateHandler>
    void SetPolicy(const std::string& tag) {
        static_assert(
            std::is_base_of<ProcessInputHandlerBase, InputHandler>::value,
            "InputHandler must derive from ProcessInputHandlerBase");
        static_assert(std::is_base_of<UpdateHandlerBase, UpdateHandler>::value,
                      "UpdateHandler must derive from UpdateHandlerBase");

        auto iter = mExecution.find(tag);
        if (iter != mExecution.end()) {
            delete iter->second->input;
            delete iter->second->update;
            delete iter->second;
            mExecution.erase(iter);
        }
        ActorExecutionPolicy* p = new ActorExecutionPolicy();
        p->input = new InputHandler();
        p->update = new UpdateHandler();
        mExecution.emplace(tag, p);
    }
};
