/*
#include "StarFallEngine.h"

#include <format>

using namespace STR_FALL;

int const WINDOW_WIDTH = 1280;
int const WINDOW_HEIGHT = 1024;

int main()
{
    STR_FALL::Renderer renderer;
    STR_FALL::Input input;
    STR_FALL::Time time;
    if (!renderer.Initialize("testing", WINDOW_WIDTH, WINDOW_HEIGHT)) { return 1; }

    SDL_Event e;
    bool quit = false;
    float rotation = 0;

    std::vector<std::vector<Vector2C>> strokes;
    std::vector<Vector2C> tempStoke;
    short mode = 0;
    short userNum = 0;
    short userNumR = 0;
    short userNumG = 0;
    short userNumB = 0;

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT)
            {
                quit = true;
                break;
            }
        }
        input.Update();
        time.Tick();

        if (input.GetMousePressed(Input::MouseButton::Left))
        {
            tempStoke.push_back(Vector2C(input.GetMousePos(), renderer.GetColor()));
        }
        if (input.GetMouseDown(Input::MouseButton::Left))
        {
            if (Vector2(Vector2(tempStoke.back().x, tempStoke.back().y), input.GetMousePos()).Magnitude() > 10)
            {
                tempStoke.push_back(Vector2C(input.GetMousePos(), renderer.GetColor()));
            }
        }
        if (input.GetMouseReleased(Input::MouseButton::Left))
        {
            tempStoke.push_back(Vector2C(input.GetMousePos(), renderer.GetColor()));
            strokes.push_back(tempStoke);
            tempStoke.clear();
        }
        if (input.GetKeyDown(SDL_SCANCODE_LCTRL) && input.GetKeyPressed(SDL_SCANCODE_Z) && strokes.size() > 0) { strokes.pop_back(); }

        if (input.GetKeyPressed(SDL_SCANCODE_C))
        {
            if (mode == 0) { mode = 1; }
        }
        if (input.GetKeyPressed(SDL_SCANCODE_R))
        {
            if (mode == 1) { mode = 2; }
        }
        if (input.GetKeyPressed(SDL_SCANCODE_G))
        {
            if (mode == 1) { mode = 3; }
        }
        if (input.GetKeyPressed(SDL_SCANCODE_B))
        {
            if (mode == 1) { mode = 4; }
        }
        if (input.GetKeyPressed(SDL_SCANCODE_RETURN))
        {
            if (mode == 1)
            {
                renderer.SetColor(Color(userNumR / 255.0f, userNumG / 255.0f, userNumB / 255.0f));
                userNumR = 0;
                userNumG = 0;
                userNumB = 0;
                mode = 0;
            }
            if (mode == 2) { userNumR = userNum; mode = 1; }
            if (mode == 3) { userNumG = userNum; mode = 1; }
            if (mode == 4) { userNumB = userNum; mode = 1; }
            userNum = 0;
        }

        if (input.GetKeyPressed(SDL_SCANCODE_0) && mode > 1)
        {
            if (userNum == 0) { userNum = 0; }
            else
            {
                userNum *= 10;
                userNum += 0;
                if (userNum > 255) { userNum = 255; }
            }
        }
        if (input.GetKeyPressed(SDL_SCANCODE_1) && mode > 1)
        {
            if (userNum == 0) { userNum = 1; }
            else
            {
                userNum *= 10;
                userNum += 1;
                if (userNum > 255) { userNum = 255; }
            }
        }
        if (input.GetKeyPressed(SDL_SCANCODE_2) && mode > 1)
        {
            if (userNum == 0) { userNum = 2; }
            else
            {
                userNum *= 10;
                userNum += 2;
                if (userNum > 255) { userNum = 255; }
            }
        }
        if (input.GetKeyPressed(SDL_SCANCODE_3) && mode > 1)
        {
            if (userNum == 0) { userNum = 3; }
            else
            {
                userNum *= 10;
                userNum += 3;
                if (userNum > 255) { userNum = 255; }
            }
        }
        if (input.GetKeyPressed(SDL_SCANCODE_4) && mode > 1)
        {
            if (userNum == 0) { userNum = 4; }
            else
            {
                userNum *= 10;
                userNum += 4;
                if (userNum > 255) { userNum = 255; }
            }
        }
        if (input.GetKeyPressed(SDL_SCANCODE_5) && mode > 1)
        {
            if (userNum == 0) { userNum = 5; }
            else
            {
                userNum *= 10;
                userNum += 5;
                if (userNum > 255) { userNum = 255; }
            }
        }
        if (input.GetKeyPressed(SDL_SCANCODE_6) && mode > 1)
        {
            if (userNum == 0) { userNum = 6; }
            else
            {
                userNum *= 10;
                userNum += 6;
                if (userNum > 255) { userNum = 255; }
            }
        }
        if (input.GetKeyPressed(SDL_SCANCODE_7) && mode > 1)
        {
            if (userNum == 0) { userNum = 7; }
            else
            {
                userNum *= 10;
                userNum += 7;
                if (userNum > 255) { userNum = 255; }
            }
        }
        if (input.GetKeyPressed(SDL_SCANCODE_8) && mode > 1)
        {
            if (userNum == 0) { userNum = 8; }
            else
            {
                userNum *= 10;
                userNum += 8;
                if (userNum > 255) { userNum = 255; }
            }
        }
        if (input.GetKeyPressed(SDL_SCANCODE_9) && mode > 1)
        {
            if (userNum == 0) { userNum = 9; }
            else
            {
                userNum *= 10;
                userNum += 9;
                if (userNum > 255) { userNum = 255; }
            }
        }



        renderer.Clear();

        for (std::vector<Vector2C>& stroke : strokes) {
            if (stroke.size() > 2)
            {
                for (size_t index = 0; index < stroke.size() - 1; index++) {
                    renderer.RenderLineColor(LineC(
                        stroke.at(index),
                        stroke.at(index + 1),
                        stroke.at(index).c
                    ));
                }
            }
            else
            {
                renderer.RenderPointColor(stroke[0]);
            }
        }

        if (tempStoke.size() > 2)
        {
            for (size_t index = 0; index < tempStoke.size() - 1; index++) {
                renderer.RenderLineColor(LineC(
                    tempStoke.at(index),
                    tempStoke.at(index + 1),
                    tempStoke.at(index).c
                ));
            }
        }

        if (mode == 1)
        {
            std::string text = std::format("New Color | R: {} | G: {} | B: {} | 0-255 scale", userNumR, userNumG, userNumB);
            renderer.RenderDebugText(text, Vector2(0, 0));
        }
        if (mode == 2)
        {
            std::string text = std::format("New Color | [R: {}] | G: {} | B: {} | 0-255 scale", userNum, userNumG, userNumB);
            renderer.RenderDebugText(text, Vector2(0, 0));
        }
        if (mode == 3)
        {
            std::string text = std::format("New Color | R: {} | [G: {}] | B: {} | 0-255 scale", userNumR, userNum, userNumB);
            renderer.RenderDebugText(text, Vector2(0, 0));
        }
        if (mode == 4)
        {
            std::string text = std::format("New Color | R: {} | G: {} | [B: {}] | 0-255 scale", userNumR, userNumG, userNum);
            renderer.RenderDebugText(text, Vector2(0, 0));
        }

        renderer.Present();
    }

    renderer.ShutDown();

    return 0;
}
*/