#include "Component.h"
#include "Actor.h"
#include "LevelLoader.h"

Component::Component(class Actor* owner, int updateOrder) : mOwner(owner), mUpdateOrder(updateOrder)
{
	mOwner->AddComponent(this);
}

Component::~Component()
{
	mOwner->RemoveComponent(this);
}

void Component::Update(float deltatime)
{}

void Component::LoadProperties(const rapidjson::Value& inObj)
{
	JsonHelper::GetInt(inObj, "updateOrder", mUpdateOrder);
}
