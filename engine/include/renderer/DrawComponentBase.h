#pragma once
#include "core/Component.h"

template <typename Renderer>
class DrawComponentBase : public Component {
   protected:
    Renderer* mSystem;

    int mDrawOrder;

   public:
    DrawComponentBase(class Actor* owner, Renderer* system,
                      int updateOrder = 100, int drawOrder = 100)
        : Component(owner, updateOrder),
          mSystem(system),
          mDrawOrder(drawOrder) {}

    virtual ~DrawComponentBase() {}

    virtual void Draw() = 0;

    Renderer* GetSystem() { return mSystem; }
};
