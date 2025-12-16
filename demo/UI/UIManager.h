#pragma once
#include <string>
#include <unordered_map>
#include <vector>

class UIManager {
    std::vector<class UIScreen*> mUIStack;

   public:
    UIManager() {};

    const std::vector<class UIScreen*>& GetUIStack() { return mUIStack; }
    void PushUI(class UIScreen* screen) { mUIStack.emplace_back(screen); }

    void Update(float deltatime);
};
