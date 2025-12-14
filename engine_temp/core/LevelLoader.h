#pragma once
#include <functional>
#include <string>
#include <unordered_map>

#include "core/Math.h"
#include "document.h"

using ActorFunc =
    std::function<class Actor*(class ActorsSystem*, const rapidjson::Value&)>;

using ComponentFunc =
    std::function<class Component*(class Actor*, const rapidjson::Value&)>;

class LevelLoader {
   public:
    static bool LoadLevel(class ActorsSystem* system,
                          const std::string& fileName);
    static bool LoadJSON(const std::string& fileName,
                         rapidjson::Document& outDoc);

   private:
    static void LoadGlobalProperties(class Game* system,
                                     const rapidjson::Value& inObject);
    static void LoadActors(class ActorsSystem* system,
                           const rapidjson::Value& inArray);
    static void LoadComponents(class Actor* owner,
                               const rapidjson::Value& inArray);

    static std::unordered_map<std::string, ActorFunc> sActorFactoryMap;
    static std::unordered_map<std::string, std::pair<int, ComponentFunc>>
        sComponentFactoryMap;
};

class JsonHelper {
   public:
    static bool GetInt(const rapidjson::Value& inObject, const char* inProperty,
                       int& outInt);
    static bool GetFloat(const rapidjson::Value& inObject,
                         const char* inProperty, float& outFloat);
    static bool GetString(const rapidjson::Value& inObject,
                          const char* inProperty, std::string& outStr);
    static bool GetBool(const rapidjson::Value& inObject,
                        const char* inProperty, bool& outBool);
    static bool GetVector3(const rapidjson::Value& inObject,
                           const char* inProperty, Vector3& outVector);
    static bool GetQuaternion(const rapidjson::Value& inObject,
                              const char* inProperty, Quaternion& outQuat);

   private:
    // 戻り値をbool値にしてエラーハンドリング？
    // quaternion, float取得で使ってる
    static float ConvertStringToFloat(const std::string);
    static Vector3 ConvertStringToVector3(const std::string);
};
