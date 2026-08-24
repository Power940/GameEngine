#include "Systems/StarFallEngine.h"
#include "SpaceGame3D.h"

using namespace STR_FALL;

int const WINDOW_WIDTH = 1920;
int const WINDOW_HEIGHT = 1080;

SpaceGame3D game;

int main()
{
    SetWorkingDirectory("Assets");

    int initCode = STR_Engine::Get().Initialize("Space Game", WINDOW_WIDTH, WINDOW_HEIGHT);
    std::cout << "INIT_CODE: " << initCode << std::endl;

    game.Initialize();
    SDL_Event SDLEvent;
    bool quit = false;

    while (!quit) {
        while (SDL_PollEvent(&SDLEvent)) {
            if (SDLEvent.type == SDL_EVENT_QUIT)
            {
                quit = true;
                break;
            }
        }
        game.Update();
        game.Draw();
    }

    game.Shutdown();

    return 0;
}