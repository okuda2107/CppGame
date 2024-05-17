#pragma once

class AudioSystem {
    public:
    AudioSystem(class Game* game);
    ~AudioSystem();

    bool Initialize();
    void Shutdown();
    void Update(float deltaTime);
    private:
    class Game* mGame;
};
