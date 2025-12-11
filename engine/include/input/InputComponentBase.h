#pragma once
#include "core/Component.h"

template <typename InputSystem>
class InputComponentBase : public Component {
   protected:
    InputSystem* mSystem;

   public:
    InputComponentBase(class Actor* owner, InputSystem* system)
        : Component(owner), mSystem(system) {}
};
