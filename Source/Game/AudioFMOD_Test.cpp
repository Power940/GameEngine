/*
#include "StarFallEngine.h"

using namespace STR_FALL;

int const WINDOW_WIDTH = 1280;
int const WINDOW_HEIGHT = 1024;

int main()
{
    int initCode = g_engine.Initialize("Testing", WINDOW_WIDTH, WINDOW_HEIGHT);
    std::cout << "INIT_CODE: " << initCode << std::endl;

    g_engine.m_audio.CreateSound("test.wav");
    g_engine.m_audio.CreateSound("snare.wav");
    g_engine.m_audio.CreateSound("bass.wav");
    g_engine.m_audio.CreateSound("clap.wav");
    g_engine.m_audio.CreateSound("close-hat.wav");
    g_engine.m_audio.CreateSound("cowbell.wav");
    g_engine.m_audio.CreateSound("open-hat.wav");

    SDL_Event SDLEvent;
    bool quit = false;

    g_engine.m_audio.PlaySound(0);

    while (!quit) {
        while (SDL_PollEvent(&SDLEvent)) {
            if (SDLEvent.type == SDL_EVENT_QUIT)
            {
                quit = true;
                break;
            }
        }

        if (g_engine.m_input.GetKeyPressed(SDL_SCANCODE_D)) { g_engine.m_audio.PlaySound(1); }
        if (g_engine.m_input.GetKeyPressed(SDL_SCANCODE_F)) { g_engine.m_audio.PlaySound(2); }
        if (g_engine.m_input.GetKeyPressed(SDL_SCANCODE_G)) { g_engine.m_audio.PlaySound(3); }
        if (g_engine.m_input.GetKeyPressed(SDL_SCANCODE_H)) { g_engine.m_audio.PlaySound(4); }
        if (g_engine.m_input.GetKeyPressed(SDL_SCANCODE_J)) { g_engine.m_audio.PlaySound(5); }
        if (g_engine.m_input.GetKeyPressed(SDL_SCANCODE_K)) { g_engine.m_audio.PlaySound(6); }

        g_engine.Update();
    }

    return 0;
}
*/