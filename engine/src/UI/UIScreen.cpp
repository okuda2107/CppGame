#include "UI/UIScreen.h"

#include "GL/glew.h"
#include "UI/Font.h"
#include "UI/UISystem.h"
#include "core/Game.h"
#include "renderer/Shader.h"
#include "renderer/Texture.h"

UIScreen::UIScreen(UISystem* system) : mSystem(system), mState(EActive) {
    // Add to UI Stack
    mSystem->PushUI(this);
    // mFont = mGame->GetFont("Assets/SlacksideOne-Regular.ttf");
}

UIScreen::~UIScreen() {
    for (auto& [name, tex] : mFontTexture) {
        tex->Unload();
    }
    mFontTexture.clear();
}

void UIScreen::DrawTexture(Shader* shader, Texture* texture,
                           const Vector2& offset, float scale) {
    // Scale the quad by the width/height of texture
    Matrix4 scaleMat = Matrix4::CreateScale(
        static_cast<float>(texture->GetWidth()) * scale,
        static_cast<float>(texture->GetHeight()) * scale, 1.0f);
    // Translate to position on screen
    Matrix4 transMat =
        Matrix4::CreateTranslation(Vector3(offset.x, offset.y, 0.0f));
    // Set world transform
    Matrix4 world = scaleMat * transMat;
    shader->SetMatrixUniform("uWorldTransform", world);
    // Set current texture
    texture->SetActive();
    // Draw quad

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}
