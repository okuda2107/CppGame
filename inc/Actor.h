#pragma once
#include "Math.h"
#include "Component.h"
#include <vector>
#include <cstdint>
#include <document.h>

class Actor {
    public:
    enum class State {
        EActive,
		EPaused,
		EDead
    };

    Actor(class Game* game);
	~Actor();

	void ProcessInput(const uint8_t* keystate);
    virtual void ActorInput(const uint8_t* keystate) {}
    void Update(float deltatime);
	void UpdateComponent(float deltatime);
	virtual void UpdateActor(float deltatime);

	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);

	class Game* GetGame() { return mGame; }
	Vector3& GetPosition() { return mPosition; }
	float GetScale() { return mScale; }
	Quaternion& GetRotation() { return mRotation; }
	State GetState() { return mState; }
	Vector3 GetForward() const { return Vector3::Transform(Vector3::UnitX, mRotation); }
	void SetState(State state) { mState = state; mRecomputeWorldTransform = true; }
	void SetScale(float scale) { mScale = scale; mRecomputeWorldTransform = true; }
	void SetPosition(Vector3 pos) { mPosition = pos; mRecomputeWorldTransform = true; }
	void SetRotation(const Quaternion& rot) { mRotation = rot; mRecomputeWorldTransform = true; }

	void ComputeWorldTransform();
	Matrix4& GetWorldTransform() { return mWorldTransform; }

	Component* GetComponentOfType(Component::TypeID type);

	virtual void LoadProperties(const rapidjson::Value& inObj);

	template <typename T> static Actor* Create(class Game* game, const rapidjson::Value& inObj)
	{
		T* t = new T(game);
		t->LoadProperties(inObj);
		return t;
	}

	private:
	Game* mGame;
	Vector3 mPosition;
	float mScale;
	Quaternion mRotation;
	State mState;

	Matrix4 mWorldTransform;
	bool mRecomputeWorldTransform;

	std::vector<class Component*> mComponents;
};
