#pragma once
#include <string>
#include "document.h"
#include "Math.h"
#include <unordered_map>
#include <functional>

using ActorFunc = std::function<
	class Actor* (class Game*, const rapidjson::Value&)
>;

using ComponentFunc = std::function<
	class Component* (class Actor*, const rapidjson::Value&)
>;

class LevelLoader
{
public:
	static bool LoadLevel(class Game* game, const std::string& fileName);
	static bool LoadJSON(const std::string& fileName, rapidjson::Document& outDoc);

private:
	static void LoadGlobalProperties(class Game* game, const rapidjson::Value& inObject);
	static void LoadActors(class Game* game, const rapidjson::Value& inArray);
	static void LoadComponents(class Actor* owner, const rapidjson::Value& inArray);

	static std::unordered_map<std::string, ActorFunc> sActorFactoryMap;
	static std::unordered_map<std::string, std::pair<int, ComponentFunc>> sComponentFactoryMap;
};

class JsonHelper
{
public:
	static bool GetInt(const rapidjson::Value& inObject, const char* inProperty, int& outInt);
	static bool GetFloat(const rapidjson::Value& inObject, const char* inProperty, float& outFloat);
	static bool GetString(const rapidjson::Value& inObject, const char* inProperty, std::string& outStr);
	static bool GetBool(const rapidjson::Value& inObject, const char* inProperty, bool& outBool);
	static bool GetVector3(const rapidjson::Value& inObject, const char* inProperty, Vector3& outVector);
	static bool GetQuaternion(const rapidjson::Value& inObject, const char* inProperty, Quaternion& outQuat);
};
