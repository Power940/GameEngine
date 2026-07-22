#pragma once
#include "Constants.h"
#include "Random.h"
#include "Structs.h"
#include "Collision.h"
#include "Renderer.h"
#include "Input.h"
#include "StarTime.h"
#include "Object.h"
#include "Audio.h"
#include "Scene.h"
#include "file.h"

namespace STR_FALL
{
	struct STR_Engine
	{
	public:
		static STR_Engine& Get() { static STR_Engine engine; return engine; }

		Renderer m_renderer;
		Input m_input;
		Time m_time;
		Audio m_audio;

		int Initialize(const char* windowName, const int WINDOW_WIDTH, const int WINDOW_HEIGHT);
		void Shutdown();
		void Update();

	private:
		STR_Engine() = default;
	};
};