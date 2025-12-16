#pragma once
#include <cstdint>
#include <functional>
#include <string>
#include <vector>

#include "core/Math.h"
#include "renderer/OpenGL/SpriteComponent.h"

namespace OpenGL {
class Texture;
class Shader;
class Font;
class SpriteComponent;
}  // namespace OpenGL

// UIの描画部分の責務を負う
class UIComponent : public OpenGL::SpriteComponent {
   protected:
    class UIManager* mSystem;
    class UIScreen* mScreen;
    OpenGL::Font* mFont;

   public:
    UIComponent(class ActorsSystem* actorSystem, class UIManager* manager,
                class Renderer* renderer);
    virtual ~UIComponent();

    void Draw(OpenGL::Shader* shader) override;
};
