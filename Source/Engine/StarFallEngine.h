#pragma once
#include "Constants.h"
#include "Random.h"
#include "Structs.h"
#include "Collision.h"
#include "Renderer.h"
#include "Input.h"
#include "StarTime.h"
#include "GameObject.h"
#include "Audio.h"
#include "Scene.h"
#include "file.h"
#include "Text.h"
#include "Game.h"
#include "ParticleSystem.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "Utils.h"
#include "Factory.h"
#include "Json.h"

namespace STR_FALL
{
	struct STR_Engine
	{
	public:
		static STR_Engine& Get() { static STR_Engine engine; return engine; }

		inline static Renderer m_renderer;
		inline static Input m_input;
		inline static Time m_time;
		inline static Audio m_audio;
		inline static ParticleSystem2D m_PS2D;

		int Initialize(const char* windowName, const int WINDOW_WIDTH, const int WINDOW_HEIGHT);
		void Shutdown();
		void Update();

	private:
		STR_Engine() = default;
	};
};