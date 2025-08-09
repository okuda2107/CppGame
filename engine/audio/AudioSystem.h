#pragma once
#include <unordered_map>

class AudioSystem {
    public:
    AudioSystem(class Game* game);
    ~AudioSystem();

    bool Initialize();
    void Shutdown();

    void UnloadData();

    void Update(float deltaTime);

    void AddAudio(class AudioComponent* audio);
    void RemoveAudio(class AudioComponent* audio);

    void test();

    private:
    class Game* mGame;

    std::unordered_map<std::string, class Sound*> mSounds;
};
