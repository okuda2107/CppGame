#pragma once
#include <cstdint>
#include "document.h"

class Component
{
public:

	enum TypeID
	{
		TComponent = 0,
		TMeshComponent,
		TMoveComponent,
		TSpriteComponent,
		TInputComponent,
		NUM_COMPONENT_TYPES
	};

	Component(class Actor* owner, int updateOrder = 100);
	~Component();

	virtual void ProcessInput(const uint8_t* keystate)
	{}

	virtual void Update(float deltatime);

	virtual void OnUpdateWorldTransform() {}

	const int GetUpdateOrder() { return mUpdateOrder; }
	virtual TypeID GetType() const = 0;

	virtual void LoadProperties(const rapidjson::Value& inObj);

	template <typename T> static Component* Create(class Actor* owner, const rapidjson::Value& inObj)
	{
		T* t = new T(owner);
		t->LoadProperties(inObj);
		return t;
	}

protected:
	class Actor* mOwner;
	int mUpdateOrder;
};
