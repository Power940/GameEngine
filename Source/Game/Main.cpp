#include "StarFallEngine.h"
#include "SpaceGame3D.h"

using namespace STR_FALL;

int const WINDOW_WIDTH = 1920;
int const WINDOW_HEIGHT = 1080;

SpaceGame3D game;

int main()
{
    SetWorkingDirectory("Assets");

#pragma region Factory stuff to be graded

    Factory::Instance().Register<Object>("Object");
    Factory::Instance().Register<GameObject>("GameObject");
    Factory::Instance().Register<Ship3D>("Ship3D");
    Factory::Instance().Register<Marker>("Marker");

    auto object = Factory::Instance().Create("Object");
    auto gameObject = Factory::Instance().Create<GameObject>("GameObject");
    auto ship = Factory::Instance().Create<Ship3D>("Ship3D");
    auto marker = Factory::Instance().Create<Marker>("Marker");

    object->m_name = "the best object";
    gameObject->m_vel = Vector3(5.0f, -15.0f, 9.0f);
    ship->m_dir = Vector3(-2.0f, 3.0f, 1.0f);
    marker->m_vel = Vector3(7.0f, 1.0f, 0.0f);


    std::cout << "Object " << object->m_name << std::endl;
    std::cout << "GameObject " << gameObject->m_vel << std::endl;
    std::cout << "ship " << ship->m_dir << std::endl;
    std::cout << "marker " << marker->m_vel << std::endl;

    return 0;

#pragma endregion

#pragma region Json print out to be graded

    rapidjson::Document doc;
    Json::Load("Data/Scene.json", doc);

    std::string buffer;
    if (ReadTextFile("Data/Data.json", buffer))
    {
        std::cout << buffer << std::endl;

        rapidjson::Document document;
        if (Json::Load("Data/Data.json", document))
        {
            std::string name;
            int age;
            float speed;
            bool isAwake;
            Vector2 position;
            Vector3 color;

            // read the json data
            JSON_READ(document, name);
            JSON_READ(document, age);
            JSON_READ(document, speed);
            JSON_READ(document, isAwake);
            JSON_READ(document, position);
            JSON_READ(document, color);

            // show the data
            std::cout << name << " " << age << " " << speed << " " << isAwake << std::endl;
            std::cout << position.m_x << " " << position.m_y << std::endl;
            std::cout << color.m_x << " " << color.m_y << " " << color.m_z << " " << std::endl;
        }
    }

#pragma endregion

    //int initCode = STR_Engine::Get().Initialize("Space Game", WINDOW_WIDTH, WINDOW_HEIGHT);
    //std::cout << "INIT_CODE: " << initCode << std::endl;

    //game.Initialize();
    //SDL_Event SDLEvent;
    //bool quit = false;

    //while (!quit) {
    //    while (SDL_PollEvent(&SDLEvent)) {
    //        if (SDLEvent.type == SDL_EVENT_QUIT)
    //        {
    //            quit = true;
    //            break;
    //        }
    //    }
    //    game.Update();
    //    game.Draw();
    //}

    //game.Shutdown();

    //return 0;
}