#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "base/DrawComponentBase.h"

class SpriteComponent : public DrawComponentBase<class Renderer> {
   public:
    SpriteComponent(class Actor* owner, Renderer* system, int drawOrder = 100);
    ~SpriteComponent();

    virtual void Draw(class Shader* shader);
    virtual void SetTexture(class Texture* tex);

    const int GetDrawOrder() { return mDrawOrder; }

    TypeID GetType() const { return TypeID::TSpriteComponent; }

   protected:
    class Texture* mTexture;
    int mDrawOrder;
    int mTexHeight;
    int mTexWidth;
};
