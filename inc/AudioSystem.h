#pragma once

class AudioSystem {
    public:
    AudioSystem(class Game* game);
    ~AudioSystem();

    bool Initialize();
    void Shutdown();
    void Update(float deltaTime);
    void test();

    private:
    class Game* mGame;
};
