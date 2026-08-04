#pragma once
#include "StarFallEngine.h"
#include "Ship3D.h"
#include "Marker.h"

using namespace STR_FALL;

enum GameState
{
	MainMenu,
	Game
};

class SpaceGame3D : public Game
{
public:
	GameState currentState = GameState::MainMenu;
	Text* menuText = nullptr;
	std::shared_ptr<Texture> texture;


	virtual bool Initialize()
	{
		m_scene = new Scene();
		m_scene->m_game = this;

		Ship3DDesc playerDesc;
		playerDesc.m_transform = Transform3D(Vector3(0, 0, 0), Vector3(20, 20, 20));
		playerDesc.m_baseMesh = SpaceShip3D;
		playerDesc.m_name = "player";
		playerDesc.m_tags = { "player" };
		playerDesc.m_cam = Camera3D(Transform3D(), 90, Vector2(static_cast<float>(STR_Engine::m_renderer.GetSreenWidth()), static_cast<float>(STR_Engine::m_renderer.GetSreenHeight())));
		playerDesc.m_forceStrength = 100.0f;
		playerDesc.m_maxVel = 1000.f;
		playerDesc.m_scene = m_scene;
		m_scene->AddObject(std::move(std::make_unique<Ship3D>(playerDesc)));

		SeedRandom();
		for (int index = 0; index < 500; index++)
		{
			ObjectDesc markerDesc;
			markerDesc.m_transform = Transform3D(
				Vector3(static_cast<float>(RandomInt(2000, -2000)), static_cast<float>(RandomInt(2000, -2000)), static_cast<float>(RandomInt(2000, -2000))),
				Vector3(10.0f, 10.0f, 10.0f),
				Matrix3::RotationXYZ(Vector3(RandomFloat(F_PI2), RandomFloat(F_PI2), RandomFloat(F_PI2)))
			);
			markerDesc.m_name = "marker color";
			markerDesc.m_tags = { "marker" };
			markerDesc.m_scene = m_scene;

			Mesh3D temp = markerMesh;
			temp.m_color = Color((markerDesc.m_transform.m_pos + 2000.0f) / 4000.0f);
			markerDesc.m_baseMesh = temp;

			markerDesc.m_collisionLayer = BitMaskInt(2);

			m_scene->AddObject(std::move(std::make_unique<Marker>(markerDesc, true)));
		}

		for (int index = 0; index < 500; index++)
		{
			ObjectDesc markerDesc;
			markerDesc.m_transform = Transform3D(
				Vector3(static_cast<float>(RandomInt(20000, -20000)), static_cast<float>(RandomInt(20000, -20000)), static_cast<float>(RandomInt(20000, -20000))),
				Vector3(10.0f, 10.0f, 10.0f),
				Matrix3::RotationXYZ(Vector3(RandomFloat(F_PI2), RandomFloat(F_PI2), RandomFloat(F_PI2)))
			);
			markerDesc.m_name = "marker no color";
			markerDesc.m_tags = { "marker" };
			markerDesc.m_baseMesh = markerMesh;
			markerDesc.m_scene = m_scene;

			m_scene->AddObject(std::move(std::make_unique<Marker>(markerDesc, false)));
		}

		Camera3D* cam = &(m_scene->GetObjectName<Ship3D>("player")->m_cam);
		STR_Engine::Get().m_renderer.SetCamera(cam);

		STR_Engine::m_audio.AddSound("shoot", "Shoot.mp3");

		Font* font = new Font();
		font->Load("Fonts/VCR_OSD_MONO.ttf", 80);
		menuText = new Text(font);
		menuText->Create(STR_Engine::m_renderer, "3D Ship Sim\nPress Space to Start", Color());

		texture = std::make_shared<Texture>();
		texture->Load("Textures/beast.png", STR_Engine::m_renderer);

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
			STR_Engine::m_renderer.DrawTexture(texture.get(), 30.0f, 30.0f);
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