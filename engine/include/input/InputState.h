#pragma once
#include "KeyboardAndMouse/KeyboardState.h"
#include "KeyboardAndMouse/MouseState.h"

// 入力機器から取得した情報をまとめた構造体
struct InputState {
    class KeyboardState* Keyboard;
    class MouseState* Mouse;

    InputState();
};

/*
本来ならすべてのコントローラを抽象化したい
アイデアとしてはそれぞれの取得値をkeyとvalueのmapで持つ
    具体的な実装の方では，keyで用いる文字列や更新処理を定義

    struct InputState {
        std::unordered_map<std::string, Union> InputInfo;
    }
*/
