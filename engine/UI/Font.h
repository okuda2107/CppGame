#pragma once
#include <string>
#include <unordered_map>

#include "Math.h"
#include "SDL_ttf.h"

class Font {
    std::unordered_map<int, TTF_Font*> mFontData;

    class Game* mGame;

   public:
    Font(class Game* game);
    ~Font();

    // ファイルのロード / アンロード
    bool Load(const std::string& filename);
    void Unload();

    class Texture* RenderText(const std::string& text,
                              const Vector3& color = Color::White,
                              int pointSize = 30);
};
