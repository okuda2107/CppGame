#pragma once
#include <string>
#include <unordered_map>
#include <vector>

/*
    RendererはSetUIを実装しているクラスを受け入れる．
*/
template <typename Renderer>
class UIManager {
    class Renderer* mRenderer;

    std::vector<class UIScreen*> mUIStack;

    std::unordered_map<std::string, class Font*> mFonts;

   public:
    UIManager();

    void HandleKeyPress(int Key);
    // clean upを行う
    void Update();
    void Draw();

    const std::vector<class UIScreen*>& GetUIStack() { return mUIStack; }
    void PushUI(class UIScreen* screen) { mUIStack.emplace_back(screen); }

    class Font* GetFont(const std::string& filename);
};
