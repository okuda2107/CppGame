#pragma once
#include "base/InputComponentBase.h"

class InputComponent : public InputComponentBase<class InputSystem> {
   public:
    InputComponent(class Actor* owner, class InputSystem* system)
        : InputComponentBase(owner, system) {}
};
