#pragma once
#include <type_traits>

#include "game/UI/UIScreen.h"
#include "game/object/Actor.h"

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
    ActorCreateDeps mSystems;

    template <typename T>
    T& GetSystem();

    // TDeps -> TypeLists を解決するための補助関数
    template <typename T, typename... Ts>
    T ResolveDeps(TypeLists<Ts...> _) {
        return T{GetSystem<Ts>()...};
    }

   public:
    ActorFactory(ActorCreateDeps acd) : mSystems(acd) {}

    // TListsの型指定の順番は，TDepsのメンバ変数の順番に依存する
    /*
        TActor: Actorの具体クラス
        TDeps: ActorDepsの具体クラス．Actorの具体クラスが引数に取る依存システムをまとめた構造体
        TLists: TDepsに注入したいシステムの型のリスト
    */
    // todo: 上手くテンプレートメタプログラミングを行えば，TActorのみの指定で良くなるらしい
    // Actorクラスの内部にTDepsやTListsの型指定を行う．このときstatic_assertで型が定義されているかをチェックする必要がある．
    template <typename TActor, typename TDeps, typename TLists>
    ActorID ActorFactory::CreateActor() {
        static_assert(std::is_base_of<Actor, TActor>::value,
                      "TActor must derive from Actor");
        static_assert(std::is_base_of<ActorDeps, TDeps>::value,
                      "TDeps must derive from ActorDeps");
        static_assert(IsTypeLists<TListss>::value,
                      "TListss must be a TypeLists<...>");

        // 依存関係depsの解決
        TDeps deps = ResolveDeps(TLists{});

        // Actor生成
        TActor* actor = new TActor(mSystems.actorsSystem, deps);
    }

    template <typename TUI, typename TDeps, typename TLists>
    UIID ActorFactory::CreateUI() {
        static_assert(std::is_base_of<UIScreen, TUI>::value,
                      "TActor must derive from UIScreen");
        static_assert(std::is_base_of<UIDeps, TDeps>::value,
                      "TDeps must derive from UIDeps");
        static_assert(IsTypeLists<TListss>::value,
                      "TListss must be a TypeLists<...>");

        // 依存関係depsの解決
        TDeps deps = ResolveDeps(TLists{});

        // Actor生成
        TActor* actor = new TUI(mSystems.uiSystem, deps);
    }
};

template <>
inline class ActorsSystem& ActorFactory::GetSystem<ActorsSystem>() {
    return mSystems.actorsSystem;
}

template <>
inline class RenderDB& ActorFactory::GetSystem<RenderDB>() {
    return mSystems.renderDB;
}
