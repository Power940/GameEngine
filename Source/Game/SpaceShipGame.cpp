#include "StarFallEngine.h"
#include "Ship3D.h"
#include "Marker.h"

using namespace STR_FALL;

int const WINDOW_WIDTH = 1920;
int const WINDOW_HEIGHT = 1080;

Scene testingLevel;

int main()
{
    int initCode = STR_Engine::Get().Initialize("Testing", WINDOW_WIDTH, WINDOW_HEIGHT);
    std::cout << "INIT_CODE: " << initCode << std::endl;

    Ship3DDesc playerDesc;
    playerDesc.m_transform = Transform3D(Vector3(0, 0, 0), Vector3(20, 20, 20));
    playerDesc.m_baseMesh = SpaceShip3D;
    playerDesc.m_name = "player";
    playerDesc.m_cam = Camera3D(Transform3D(), 90, Vector2(WINDOW_WIDTH, WINDOW_HEIGHT));
    playerDesc.m_forceStrength = 500.0f;
    playerDesc.m_maxVel = 1000.f;
    playerDesc.m_scene = &testingLevel;
    testingLevel.AddObject(new Ship3D(playerDesc));

    SDL_Event SDLEvent;
    bool quit = false;

    SeedRandom();
    for (int index = 0; index < 1000; index++)
    {
        ObjectDesc<Transform3D, Mesh3D> markerDesc;
        markerDesc.m_transform = Transform3D(
            Vector3(RandomInt(1000, -1000), RandomInt(1000, -1000), RandomInt(1000, -1000)),
            Vector3(10, 10, 10),
            Vector3(RandomFloat(F_PI2), RandomFloat(F_PI2), RandomFloat(F_PI2))
        );
        Mesh3D temp = markerMesh;
        temp.m_color = Color((markerDesc.m_transform.m_pos + 1000.0f) / 2000.0f);
        markerDesc.m_baseMesh = temp;
        markerDesc.m_scene = &testingLevel;
        Marker* tempMarker = new Marker(markerDesc);
        tempMarker->m_canMove = ((index % 2 == 0) ? false : true);

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
        STR_Engine::Get().Update();

        testingLevel.Update(STR_Engine::Get().m_time.GetDeltaTime());

        STR_Engine::Get().m_renderer.Clear();

        Ship3D* player = testingLevel.GetObjectName<Ship3D>("player");
        Camera3D cam;
        cam = player->m_cam;

        testingLevel.Draw(STR_Engine::Get().m_renderer, cam);

        STR_Engine::Get().m_renderer.Present();
    }

    return 0;
}