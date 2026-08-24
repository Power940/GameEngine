#pragma once
#include "Utils/Constants.h"
#include "Random.h"
#include "Types/Structs.h"
#include "Renderer.h"
#include "Input.h"
#include "StarTime.h"
#include "Types/GameObject.h"
#include "Audio.h"
#include "GameContainers/Scene.h"
#include "File/file.h"
#include "Types/Text.h"
#include "GameContainers/Game.h"
#include "ParticleSystem.h"
#include "Types/Texture.h"
#include "ResourceManager.h"
#include "Utils/Utils.h"
#include "Factory.h"
#include "File/Json.h"
#include "Physics.h"


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
		inline static Physics m_phys;

		int Initialize(const char* windowName, const int WINDOW_WIDTH, const int WINDOW_HEIGHT);
		void Shutdown();
		void Update();

	private:
		STR_Engine() = default;
	};
};