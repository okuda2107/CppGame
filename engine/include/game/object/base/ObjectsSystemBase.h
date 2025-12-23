#pragma once

// Actorの配列を保持し，それらのupdateを保証する
template <typename InputState>
class ObjectsSystemBase {
   public:
    virtual void UnloadObjects() = 0;

    virtual void ProcessInput(const InputState& state) = 0;
    virtual void UpdateObjects(float deltatime) = 0;
};
