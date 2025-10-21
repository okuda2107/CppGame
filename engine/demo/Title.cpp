#include "Title.h"

#include "Bonfire.h"
#include "FPSActor.h"
#include "Game.h"
#include "SDL.h"

Title::Title(Game* game) : UIScreen(game) {
    mGame->SetState(Game::EPaused);
    SetTitle("Chillut's Fire", Color::White, 72);
    new Bonfire(game);
    FPSActor* fa = new FPSActor(game);
    fa->SetForwardSpeed(60.0f);
    fa->SetStrafeSpeed(60.0f);
}
