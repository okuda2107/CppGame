#pragma once
#include <cstdint>

#include "document.h"

class Component {
   public:
    enum TypeID {
        TComponent = 0,
        TMoveComponent,
        TSpriteComponent,
        TInputComponent,
        TAudioComponent,
        TFPSComponent,
        NUM_COMPONENT_TYPES
    };

    Component(class Actor* owner, int updateOrder = 100);
    virtual ~Component();

    virtual void ProcessInput(const class InputState& keystate) {}

    virtual void Update(float deltatime);

    virtual void OnUpdateWorldTransform() {}

    class Actor* GetOwner() const { return mOwner; }
    const int GetUpdateOrder() { return mUpdateOrder; }
    virtual TypeID GetType() const { return TComponent; }

    virtual void LoadProperties(const rapidjson::Value& inObj);

    template <typename T>
    static Component* Create(class Actor* owner,
                             const rapidjson::Value& inObj) {
        T* t = new T(owner);
        t->LoadProperties(inObj);
        return t;
    }

   protected:
    class Actor* mOwner;
    int mUpdateOrder;
};
