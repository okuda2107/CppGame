#include "input/KeyboardAndMouse/InputSystem.h"

#include "input/KeyboardAndMouse/InputState.h"

enum class EventType : Uint32 {
    QUIT = SDL_QUIT,

    KEYDOWN = SDL_KEYDOWN,
    KEYUP = SDL_KEYUP,
    TEXTEDITING = SDL_TEXTEDITING,
    TEXTINPUT = SDL_TEXTINPUT,
    KEYMAPCHANGED = SDL_KEYMAPCHANGED,
    TEXTEDITING_EXT = SDL_TEXTEDITING_EXT,

    MOUSEMOTION = SDL_MOUSEMOTION,
    MOUSEBUTTONDOWN = SDL_MOUSEBUTTONDOWN,
    MOUSEBUTTONUP = SDL_MOUSEBUTTONUP,
    MOUSEWHEEL = SDL_MOUSEWHEEL,
};

KeyboardAndMouse::InputSystem::InputSystem() {}

bool KeyboardAndMouse::InputSystem::Initialize() {
    // キーボード
    mState.Keyboard = new KeyboardState();
    // 現在の状態を示すポインタを保存
    mState.Keyboard->mCurrState = SDL_GetKeyboardState(NULL);
    // 前回の状態を示すメモリをクリア
    memset(mState.Keyboard->mPrevState, 0, SDL_NUM_SCANCODES);

    // マウス
    mState.Mouse = new MouseState();
    mState.Mouse->mCurrButtons = 0;
    mState.Mouse->mPrevButtons = 0;
    mState.Mouse->mIsRelative = false;

    return true;
}

void KeyboardAndMouse::InputSystem::Shutdown() {
    delete mState.Keyboard;
    delete mState.Mouse;
}

void KeyboardAndMouse::InputSystem::ProcessEvent(Event& event) {
    switch (event.type) {
        case SDL_MOUSEWHEEL:
            mState.Mouse->mScrollWheel =
                Vector2(static_cast<float>(event.wheel.x),
                        static_cast<float>(event.wheel.y));
            break;
    }
}

void KeyboardAndMouse::InputSystem::PrepareForUpdate() {
    // キーボード
    memcpy(mState.Keyboard->mPrevState, mState.Keyboard->mCurrState,
           SDL_NUM_SCANCODES);

    // マウス
    mState.Mouse->mPrevButtons = mState.Mouse->mCurrButtons;
    mState.Mouse->mScrollWheel = Vector2::Zero;
}

void KeyboardAndMouse::InputSystem::Update() {
    // マウス
    int x = 0, y = 0;
    if (mState.Mouse->mIsRelative) {
        mState.Mouse->mCurrButtons = SDL_GetRelativeMouseState(&x, &y);
    } else {
        mState.Mouse->mCurrButtons = SDL_GetMouseState(&x, &y);
    }
    mState.Mouse->mMousePos.x = static_cast<float>(x);
    mState.Mouse->mMousePos.y = static_cast<float>(y);
}

void KeyboardAndMouse::InputSystem::SetRelativeMouseMode(bool value) {
    SDL_bool set = value ? SDL_TRUE : SDL_FALSE;
    SDL_SetRelativeMouseMode(set);
    mState.Mouse->mIsRelative = value;
}

int KeyboardAndMouse::PollEvent(Event* event) { return SDL_PollEvent(event); }
