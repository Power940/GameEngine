#include "StarFallEngine.h"
#include "Ship.h"
#include "Ship3D.h"
#include "Marker.h"

using namespace STR_FALL;

int const WINDOW_WIDTH = 1240;
int const WINDOW_HEIGHT = 1080;

//Ship player = Ship(Transform2D(Vector2(100, 100), Vector2(75, 75)), Color(), 500.0f, 1000.0f);
Ship3D* player = new Ship3D(
    Transform3D(Vector3(0, 0, 0), Vector3(20, 20, 20)),
    Camera3D(Transform3D(), 90, Vector2(WINDOW_WIDTH, WINDOW_HEIGHT)),
    500.0f,
    1000.0f
);
Scene testingLevel;

int main()
{
    int initCode = g_engine.Initialize("Testing", WINDOW_WIDTH, WINDOW_HEIGHT);
    std::cout << "INIT_CODE: " << initCode << std::endl;
    testingLevel.AddObject(player);

    SDL_Event SDLEvent;
    bool quit = false;

    SeedRandom();
    for (int index = 0; index < 50; index++)
    {
        Marker* tempMarker = new Marker(Transform3D(
            Vector3(RandomInt(1000, -1000), RandomInt(1000, -1000), RandomInt(1000, -1000)),
            Vector3(10, 10, 10),
            Vector3(RandomFloat(F_PI2), RandomFloat(F_PI2), RandomFloat(F_PI2))
        ));

        Mesh3D tempMesh = tempMarker->GetBaseMesh();
        Vector3 tempPosAsColor = (tempMarker->GetTransform().m_pos + 1000.0f) / 2000.0f;
        tempMesh.m_color = Color(tempPosAsColor.m_x, tempPosAsColor.m_y, tempPosAsColor.m_z);
        tempMarker->SetBaseMesh(tempMesh);

        testingLevel.AddObject(tempMarker);
    }

    while (!quit) {
        while (SDL_PollEvent(&SDLEvent)) {
            if (SDLEvent.type == SDL_EVENT_QUIT)
            {
                quit = true;
                break;
            }
        }
        g_engine.Update();

        testingLevel.Update(g_engine.m_time.GetDeltaTime());

        g_engine.m_renderer.Clear();

        testingLevel.Draw(g_engine.m_renderer, ((Ship3D*)(testingLevel.GetObject(0)))->m_cam);

        g_engine.m_renderer.Present();
    }

    return 0;
}