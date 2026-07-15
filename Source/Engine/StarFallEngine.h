#pragma once
#include "Constants.h"
#include "Random.h"
#include "Structs.h"
#include "Collision.h"
#include "Renderer.h"
#include "Input.h"
#include "StarTime.h"
#include "Object.h"

namespace STR_FALL
{
	struct STR_Engine
	{
		Renderer m_renderer;
		Input m_input;
		Time m_time;

		STR_Engine() = default;

		bool Initialize(const char* windowName, const int WINDOW_WIDTH, const int WINDOW_HEIGHT);
		void Shutdown();
		void Update();
	};

	extern STR_Engine g_engine;
};