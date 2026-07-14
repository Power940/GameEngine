#include "StarFallEngine.h"

using namespace STR_FALL;

int const WINDOW_WIDTH = 1280;
int const WINDOW_HEIGHT = 1024;

Rect3D block = Rect3D(Transform3D(Vector3(0, 0, 20), Vector3(10, 10, 10)));
Camera3D cam = Camera3D(Transform3D(), 90, Vector2(WINDOW_WIDTH, WINDOW_HEIGHT));
int main()
{
    STR_FALL::Renderer r;
    if (!r.Initialize("testing", WINDOW_WIDTH, WINDOW_HEIGHT)) { return 1; }
    STR_FALL::Input input;
    STR_FALL::Time time;

    SDL_Event e;
    bool quit = false;
    float rotation = 0;

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

        rotation += time.GetDeltaTime() * 0.1f;

        block.DegZ(rotation);
        block.UpdateTriangles();

        r.Clear();

        r.SetColor(Color(0.0f, 1.0f, 1.0f));

        //r.Render3DFillTriangles(cam, block.GetTris());

        r.Present();
    }

    r.ShutDown();

    return 0;
}