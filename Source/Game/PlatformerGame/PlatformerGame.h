#pragma once
#include "StarFallEngine.h"
#include "../SpaceGame_OLD/Ship3D.h"
#include "../SpaceGame_OLD/Marker.h"
#include "../SpaceGame_OLD/Assets.h"
#include <Core/File.h>

using namespace STR_FALL;

enum GameState
{
	MainMenu,
	Game
};

class PlatformerGame : public Game
{
public:
	GameState currentState = GameState::MainMenu;
	Text* menuText;

	virtual bool Initialize()
	{
		SetWorkingDirectory("PlatformerGame");

		m_scene = std::make_unique<Scene>();
		m_scene->m_game = this;

#pragma region GameObjectSetup

		m_scene->Load("Scenes/Scene.json");

#pragma endregion

		Camera3D* cam = &(m_scene->GetObjectName<Ship3D>("PlayerShip")->m_cam);
		STR_Engine::Get().m_renderer.SetCamera(cam);

		//STR_Engine::m_audio.AddSound("shoot", "Shoot.mp3");

		menuText = new Text(ResourceManager::ResManager().GetWithID<Font>("title_font", "Fonts/VCR_OSD_MONO.ttf", 64.0f));
		menuText->Create(STR_Engine::m_renderer, "3D Platformer - Press Space to Start", Color());

		return true;
	}

	virtual void Shutdown()
	{
		STR_Engine::Get().Shutdown();
	}

	virtual void Update()
	{
		STR_Engine::Get().Update();

		if (currentState == GameState::MainMenu)
		{
			if (STR_Engine::m_input.GetKeyPressed(Input::VK_SPACE))
			{
				currentState = GameState::Game;
			}
		}
		else if (currentState == GameState::Game)
		{
			m_scene->Update(STR_Engine::m_time.GetDeltaTime());
		}
	}

	virtual void Draw()
	{
		if (currentState == GameState::MainMenu)
		{
			STR_Engine::m_renderer.Clear();
			menuText->Draw(STR_Engine::m_renderer, 100.0f, 100.0f);
			STR_Engine::m_renderer.Present();
		}
		else if (currentState == GameState::Game)
		{
			STR_Engine::m_renderer.Clear();
			m_scene->Draw(STR_Engine::m_renderer);
			STR_Engine::m_renderer.Present();
		}
	}
};