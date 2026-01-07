#include "UIManager.h"

#include "UIScreen.h"

void UIManager::Update(float deltatime) {
    // UIの更新
    for (auto ui : mUIStack) {
        if (ui->GetState() == UIScreen::EActive) {
            ui->Update(deltatime);
        }
    }
    // close状態のUIを削除
    auto iter = mUIStack.begin();
    while (iter != mUIStack.end()) {
        if ((*iter)->GetState() == UIScreen::EClosing) {
            delete *iter;
            iter = mUIStack.erase(iter);
        } else {
            ++iter;
        }
    }
}
