#pragma once

class SceneManager {
   public:
    void RequestChange(SceneID next);
    void Update(float deltatime);
    Scene& CurrentScene();
};
