#pragma once

class AudioSystem {
    public:
    AudioSystem(class Game* game);

    bool Initialize();

    private:
    class Gamd* mGame;
}
