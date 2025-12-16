#pragma once
#include <vector>

#include "Component.h"
#include "ObjectBase.h"
#include "core/Math.h"
#include "document.h"

class Actor : public ObjectBase {
   public:
    enum class State {
        EActive,
        EPaused,
        EDead,
    };

   private:
    class Game* mGame;
    Vector3 mPosition;
    float mScale;
    Quaternion mRotation;
    State mState;

    Matrix4 mWorldTransform;
    bool mRecomputeWorldTransform;

    virtual void UpdateActor(float deltatime) {};
    void UpdateComponent(float deltatime);

    std::vector<class Component*> mComponents;

   public:
    Actor(class Game* game);
    virtual ~Actor();

    void Update(float deltatime) override;

    Vector3 GetPosition() { return mPosition; }
    float GetScale() { return mScale; }
    Quaternion GetRotation() { return mRotation; }
    State GetState() { return mState; }
    Vector3 GetForward() const {
        return Vector3::Transform(Vector3::UnitX, mRotation);
    }
    Vector3 GetRight() const {
        return Vector3::Transform(Vector3::UnitY, mRotation);
    }
    Vector3 GetUp() const { return Vector3::UnitZ; }

    void SetState(State state) {
        mState = state;
        mRecomputeWorldTransform = true;
    }
    void SetScale(float scale) {
        mScale = scale;
        mRecomputeWorldTransform = true;
    }
    void SetPosition(Vector3 pos) {
        mPosition = pos;
        mRecomputeWorldTransform = true;
    }
    void SetRotation(const Quaternion& rot) {
        mRotation = rot;
        mRecomputeWorldTransform = true;
    }

    void ComputeWorldTransform();
    Matrix4& GetWorldTransform() { return mWorldTransform; }

    void AddComponent(class Component* component);
    void RemoveComponent(class Component* component);
    /*
    Component* GetComponentOfType(Component::TypeID type);

    void LoadProperties(const rapidjson::Value& inObj);

    template <typename T>
    static Actor* Create(class ActorsSystem* system,
                         const rapidjson::Value& inObj) {
        T* t = new T(system);
        t->LoadProperties(inObj);
        return t;
    }
    */
};
