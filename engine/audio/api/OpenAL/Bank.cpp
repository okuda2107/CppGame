#include "Bank.h"

OpenAL::Bank::Bank() {}
OpenAL::Bank::~Bank() {}

/*
Bankデータをロードする
ロードに成功したらtrue，失敗したらfalseを返す
Bankデータはjson形式のファイルで記述する
Notes: JSONデータのフォーマット
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
bool OpenAL::Bank::Load(const std::string& name) {
    ;
    ;
}
