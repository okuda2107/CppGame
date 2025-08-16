#include "Bank.h"

#include <fstream>
#include <sstream>

#include "SDL_log.h"
#include "api/OpenAL/Event.h"
#include "api/OpenAL/System.h"
#include "document.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/schema.h"
#include "rapidjson/stringbuffer.h"

OpenAL::Bank::Bank() {}
OpenAL::Bank::~Bank() {}

/*
Bankデータをロードする
ロードに成功したらtrue，失敗したらfalseを返す
Bankデータはjson形式のファイルで記述する
*/
bool OpenAL::Bank::Load(const std::string& fileName,
                        class OpenAL::System* system) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        SDL_Log("File not found: Bank %s", fileName.c_str());
        return false;
    }
    rapidjson::IStreamWrapper isw(file);
    rapidjson::Document doc;
    doc.ParseStream(isw);

    if (!doc.IsObject()) {
        SDL_Log("Invalid bank data: %s", fileName.c_str());
        return false;
    }

    if (!doc.HasMember("bankName") || !doc["bankName"].IsString()) {
        SDL_Log("Failed to get bank name: %s", fileName.c_str());
        return false;
    }

    // versionごとにフォーマットを分ける
    int ver = -1;
    if (doc.HasMember("version")) {
        ver = doc["version"].GetInt();
    }
    switch (ver) {
        case 1:
            return LoadVersion1(doc);

        default:
            SDL_Log("Invalid bank file version: %s", fileName.c_str());
            return false;
    }
}

/*
Notes: ver1のフォーマット
{
    "bankName": "MainBank",
    "version": 1,
    "events": [
        {
            "id": "bgm_main",
            "file": "audio/bgm_main.ogg",
            "stream": false,
            "loop": true,
            "volume": 1.0,
            "pitch": 1.0
        },
        {
            :
        },
    ]
}
*/
bool OpenAL::Bank::LoadVersion1(rapidjson::Document& doc) {
    // スキーマ読み込み
    const char* schemaJson = R"({
        "type": "object",
        "required": ["bankName", "version", "events"],
        "properties": {
            "bankName": {"type": "string"},
            "version": {"type": "integer"},
            "events": {
                "type": "array",
                "items": {
                    "type": "object",
                    "required": ["id", "file"],
                    "properties": {
                        "id": {"type": "string"},
                        "file": {"type": "string"},
                        "stream": {"type": "boolean"},
                        "loop": {"type": "boolean"},
                        "volume": {"type": "number"},
                        "pitch": {"type": "number"}
                    }
                }
            }
        }
    })";
    rapidjson::Document schemaDoc;
    schemaDoc.Parse(schemaJson);

    // バリデーション
    rapidjson::SchemaDocument schema(schemaDoc);
    rapidjson::SchemaValidator validator(schema);

    if (!doc.Accept(validator)) {
        SDL_Log("Invalid schema");
        return false;
    }

    // イベント情報のパース
    const rapidjson::Value& events = doc["events"];

    for (rapidjson::SizeType i = 0; i < events.Size(); i++) {
        // サウンドファイルのロード，格納
        std::string soundFileName = events[i]["file"].GetString();
        auto soundIter = mSounds.find(soundFileName);
        if (soundIter == mSounds.end()) {
            alutGetError();
            ALuint buffer = alutCreateBufferFromFile(soundFileName.c_str());
            if (buffer == AL_NONE) {
                ALenum error = alutGetError();
                SDL_Log("Failed to load sound data: %s: %s",
                        soundFileName.c_str(), alutGetErrorString(error));
                return false;
            }
            mSounds.emplace(soundFileName, buffer);
        }

        // イベントデータの作成，格納
        std::string id = events[i]["id"].GetString();
        auto eventIter = mEvents.find(id);
        if (eventIter == mEvents.end()) {
            OpenAL::Event* e = new OpenAL::Event();
            e->mSoundID = soundFileName;
            e->mIsStream = events[i]["stream"].GetBool();
            e->mIsLoop = events[i]["loop"].GetBool();
            e->mVolume = events[i]["volume"].GetFloat();
            e->mPitch = events[i]["pitch"].GetFloat();

            mEvents.emplace(id, e);
        }
    }
    return true;
}

bool OpenAL::Bank::Unload() {
    alGetError();
    // サウンドバッファのメモリ開放
    std::vector<ALuint> buffers;
    buffers.reserve(mSounds.size());
    for (auto& sound : mSounds) {
        buffers.push_back(sound.second);
    }
    alutGetError();
    alDeleteBuffers(buffers.size(), buffers.data());
    ALenum error = alutGetError();
    if (error != ALUT_ERROR_NO_ERROR) {
        SDL_Log("Failed to delete buffer: %s", alutGetErrorString(error));
        return false;
    }

    // イベントのメモリ解放
    for (auto event : mEvents) {
        delete event.second;
    }

    mEvents.clear();
    mSounds.clear();

    return true;
}
