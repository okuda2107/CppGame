#pragma once
#include <type_traits>

template <typename... T>
struct TypeLists {};

// 判定用traits
template <typename T>
struct IsTypeLists : std::false_type {};

template <typename... Ts>
struct IsTypeLists<TypeLists<Ts...>> : std::true_type {};

struct ActorCreateDeps {
    /*
        Sceneの生成ではactorの存在が前提となっているため，
        ObjectsSystemBaseではなく，
        ActorsSystemの方を依存関係に含める
    */
    class ActorsSystem& actorsSystem;
    class RenderDB& renderDB;
    class AudioSystem& audioSystem;
    // class PhysicsSystem& physicsSystem;
    class UISystem& uiSystem;
    class StateManager& stateManager;
    class RuntimeRequestManager& runtimeReqManager;
};

class ActorFactory {
    class ActorsSystem& mActorsSystem;
    class RenderDB& mRenderDB;
    class AudioSystem& mAudioSystem;
    // class PhysicsSystem& mPhysicsSystem;
    class UISystem& mUISystem;
    class StateManager& mStateManager;
    class RuntimeRequestManager& mRuntimeReqManager;

    template <typename T>
    T& GetSystem();

   public:
    template <typename TActor, typename TDeps>
    ActorID CreateActor() {
        static_assert(std::is_base_of<Actor, TActor>::value,
                      "TActor must derive from Actor");
        static_assert(IsTypeLists<TDeps>::value,
                      "TDeps must be a TypeLists<...>");

        // 依存関係depsの解決

        // Actor生成
        TActor* actor = new TActor(mActorsSystem, deps);
    };
};

template <>
inline class ActorsSystem& ActorFactory::GetSystem<ActorsSystem>() {
    return mActorsSystem;
}

template <>
inline class RenderDB& ActorFactory::GetSystem<RenderDB>() {
    return mRenderDB;
}
