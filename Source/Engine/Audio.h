#pragma once
#include <fmod.hpp>
#include <vector>

namespace STR_FALL
{
	class Audio
	{
	private:
		FMOD::System* audio;
		void* extraDriverData = nullptr;
		std::vector<FMOD::Sound*> sounds;
		FMOD::Sound* tempSound = nullptr;

	public:
		bool Initialize();
		void ShutDown();

		void CreateSound(const char* fileName);
		void PlaySound(int soundIndex, bool paused = false);
		void Update();
	};
}