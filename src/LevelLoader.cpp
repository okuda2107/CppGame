#include "LevelLoader.h"
#include <fstream>
#include <vector>
#include "SDL.h"
#include "Game.h"
#include "Math.h"
#include "Renderer.h"
#include <unordered_map>
#include <string>
#include "Actor.h"
#include "MeshComponent.h"
#include "MoveComponent.h"
#include "SpriteComponent.h"
#include "InputComponent.h"

std::unordered_map<std::string, ActorFunc> LevelLoader::sActorFactoryMap = {
	{ "Actor", &Actor::Create<Actor> },
};

std::unordered_map<std::string, std::pair<int, ComponentFunc>> LevelLoader::sComponentFactoryMap = {
	{"MeshComponent",
		{Component::TypeID::TMeshComponent, &Component::Create<MeshComponent>}
	},
	{"MoveComponent",
		{Component::TypeID::TMoveComponent, &Component::Create<MoveComponent>}
	},
	{"SpriteComponent",
	{Component::TypeID::TSpriteComponent, &Component::Create<SpriteComponent>}
	},
	{"InputComponent",
	{Component::TypeID::TInputComponent, &Component::Create<InputComponent>}
	}
};

const int LevelVersion = 1;

bool LevelLoader::LoadLevel(Game* game, const std::string& fileName)
{
	rapidjson::Document doc;
	if (!LoadJSON(fileName, doc))
	{
		SDL_Log("Failed to load level %s", fileName.c_str());
		return false;
	}

	int version = 0;
	if (!JsonHelper::GetInt(doc, "version", version) ||
		version != LevelVersion)
	{
		SDL_Log("Incorrect level file version for %s", fileName.c_str());
		return false;
	}

	// Handle any global properties
	const rapidjson::Value& globals = doc["globalProperties"];
	if (globals.IsObject())
	{
		LoadGlobalProperties(game, globals);
	}

	const rapidjson::Value& actors = doc["actors"];
	if (actors.IsArray())
	{
		LoadActors(game, actors);
	}

	return true;
}

bool LevelLoader::LoadJSON(const std::string& fileName, rapidjson::Document& outDoc)
{
	// Load the file from disk into an ifstream in binary mode,
	// loaded with stream buffer at the end (ate)
	std::ifstream file(fileName, std::ios::in | std::ios::binary | std::ios::ate);
	if (!file.is_open())
	{
		SDL_Log("File %s not found", fileName.c_str());
		return false;
	}

	// Get the current position in stream buffer, which is size of file
	std::ifstream::pos_type fileSize = file.tellg();
	// Seek back to start of file
	file.seekg(0, std::ios::beg);

	// Create a vector of size + 1 (for null terminator)
	std::vector<char> bytes(static_cast<size_t>(fileSize) + 1);
	// Read in bytes into vector
	file.read(bytes.data(), static_cast<size_t>(fileSize));

	// Load raw data into RapidJSON document
	outDoc.Parse(bytes.data());
	if (!outDoc.IsObject())
	{
		SDL_Log("File %s is not valid JSON", fileName.c_str());
		return false;
	}

	return true;
}

void LevelLoader::LoadGlobalProperties(Game* game, const rapidjson::Value& inObject)
{
	// Get ambient light
	Vector3 ambient;
	if (JsonHelper::GetVector3(inObject, "ambientLight", ambient))
	{
		game->GetRenderer()->SetAmbientLight(ambient);
	}

	// Get directional light
	const rapidjson::Value& dirObj = inObject["directionalLight"];
	if (dirObj.IsObject())
	{
		DirectionalLight& light = game->GetRenderer()->GetDirectionalLight();

		// Set direction/color, if they exist
		JsonHelper::GetVector3(dirObj, "direction", light.mDirection);
		JsonHelper::GetVector3(dirObj, "color", light.mDiffuseColor);
	}
}

void LevelLoader::LoadActors(Game* game, const rapidjson::Value& inArray)
{
	// Loop through array of actors
	for (rapidjson::SizeType i = 0; i < inArray.Size(); i++)
	{
		const rapidjson::Value& actorObj = inArray[i];
		if (actorObj.IsObject())
		{
			// Get the type
			std::string type;
			if (JsonHelper::GetString(actorObj, "type", type))
			{
				// Is this type in the map?
				auto iter = sActorFactoryMap.find(type);
				if (iter != sActorFactoryMap.end())
				{
					// Construct with function stored in map
					Actor* actor = iter->second(game, actorObj["properties"]);
					// Get the actor's components
					if (actorObj.HasMember("components"))
					{
						const rapidjson::Value& components = actorObj["components"];
						if (components.IsArray())
						{
							LoadComponents(actor, components);
						}
					}
				}
				else
				{
					SDL_Log("Unknown actor type %s", type.c_str());
				}
			}
		}
	}
}

void LevelLoader::LoadComponents(Actor* actor, const rapidjson::Value& inArray)
{
	// Loop through array of components
	for (rapidjson::SizeType i = 0; i < inArray.Size(); i++)
	{
		const rapidjson::Value& compObj = inArray[i];
		if (compObj.IsObject())
		{
			// Get the type
			std::string type;
			if (JsonHelper::GetString(compObj, "type", type))
			{
				auto iter = sComponentFactoryMap.find(type);
				if (iter != sComponentFactoryMap.end())
				{
					// Get the typeid of component
					Component::TypeID tid = static_cast<Component::TypeID>(iter->second.first);
					// Does the actor already have a component of this type?
					Component* comp = actor->GetComponentOfType(tid);
					if (comp == nullptr)
					{
						// It's a new component, call function from map
						comp = iter->second.second(actor, compObj["properties"]);
					}
					else
					{
						// It already exists, just load properties
						comp->LoadProperties(compObj["properties"]);
					}
				}
				else
				{
					SDL_Log("Unknown component type %s", type.c_str());
				}
			}
		}
	}
}

bool JsonHelper::GetInt(const rapidjson::Value& inObject, const char* inProperty, int& outInt)
{
	// Check if this property exists
	auto itr = inObject.FindMember(inProperty);
	if (itr == inObject.MemberEnd())
	{
		return false;
	}

	// Get the value type, and check it's an integer
	auto& property = itr->value;
	if (!property.IsInt())
	{
		return false;
	}

	// We have the property
	outInt = property.GetInt();
	return true;
}

bool JsonHelper::GetFloat(const rapidjson::Value& inObject, const char* inProperty, float& outFloat)
{
	auto itr = inObject.FindMember(inProperty);
	if (itr == inObject.MemberEnd())
	{
		return false;
	}

	auto& property = itr->value;

	if (property.IsString()) {
		std::string str = property.GetString();
		if (str == "Pi") outFloat = Math::Pi;
		else if (str == "PiOver2") outFloat = Math::PiOver2;
		else if (str == "TwoPi") outFloat = Math::TwoPi;
		else return false;
		return true;
	}

	if (property.IsDouble()) {
		outFloat = property.GetDouble();
		return true;
	}

	return false;
}

bool JsonHelper::GetString(const rapidjson::Value& inObject, const char* inProperty, std::string& outStr)
{
	auto itr = inObject.FindMember(inProperty);
	if (itr == inObject.MemberEnd())
	{
		return false;
	}

	auto& property = itr->value;
	if (!property.IsString())
	{
		return false;
	}

	outStr = property.GetString();
	return true;
}

bool JsonHelper::GetBool(const rapidjson::Value& inObject, const char* inProperty, bool& outBool)
{
	auto itr = inObject.FindMember(inProperty);
	if (itr == inObject.MemberEnd())
	{
		return false;
	}

	auto& property = itr->value;
	if (!property.IsBool())
	{
		return false;
	}

	outBool = property.GetBool();
	return true;
}

bool JsonHelper::GetVector3(const rapidjson::Value& inObject, const char* inProperty, Vector3& outVector)
{
	auto itr = inObject.FindMember(inProperty);
	if (itr == inObject.MemberEnd())
	{
		return false;
	}

	auto& property = itr->value;
	if (!property.IsArray() || property.Size() != 3)
	{
		return false;
	}

	for (rapidjson::SizeType i = 0; i < 3; i++)
	{
		if (!property[i].IsDouble())
		{
			return false;
		}
	}

	outVector.x = property[0].GetDouble();
	outVector.y = property[1].GetDouble();
	outVector.z = property[2].GetDouble();

	return true;
}

bool JsonHelper::GetQuaternion(const rapidjson::Value& inObject, const char* inProperty, Quaternion& outQuat)
{
	auto itr = inObject.FindMember(inProperty);
	if (itr == inObject.MemberEnd())
	{
		return false;
	}

	auto& property = itr->value;

	for (rapidjson::SizeType i = 0; i < 4; i++)
	{
		if (!property[i].IsDouble())
		{
			return false;
		}
	}

	outQuat.x = property[0].GetDouble();
	outQuat.y = property[1].GetDouble();
	outQuat.z = property[2].GetDouble();
	outQuat.w = property[3].GetDouble();

	return true;
}
