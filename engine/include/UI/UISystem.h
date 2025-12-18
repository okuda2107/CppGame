#pragma once
#include <vector>

class UISystem {
    std::vector<class UIScreen*> mUIStack;

   public:
    std::vector<class UIScreen*> GetUIStack() { return mUIStack; }
    void PushUI(class UIScreen* screen) { mUIStack.emplace_back(screen); }
};
