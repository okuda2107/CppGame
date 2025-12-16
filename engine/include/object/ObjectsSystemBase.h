#pragma once

class ObjectsSystemBase {
   public:
    virtual void UnloadObjects() = 0;
    virtual void UpdateObjects(float deltatime) = 0;
};
