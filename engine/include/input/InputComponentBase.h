#pragma once
#include "core/Component.h"

template <typename InputSystem>
class InputComponentBase : public Component {
   protected:
    InputSystem* mSystem;

   public:
    InputComponentBase(class Actor* owner, InputSystem* system,
                       int updateOrder = 100)
        : Component(owner, updateOrder), mSystem(system) {}

    virtual ~InputComponentBase() {}

    InputSystem* GetSystem() { return mSystem; }
};
