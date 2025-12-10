#pragma once
#include "input/InputComponentBase.h"

namespace KeyboardAndMouse {
class InputComponent : public InputComponentBase<class InputSystem> {
   public:
    InputComponent(class Actor* owner, class InputSystem* system)
        : InputComponentBase(owner, system) {}
};
}  // namespace KeyboardAndMouse
