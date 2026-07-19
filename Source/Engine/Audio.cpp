#include "Audio.h"

namespace STR_FALL
{
	bool Audio::Initialize()
	{
		if (FMOD::System_Create(&audio) != FMOD_OK) { return false; }
		if (audio->init(32, FMOD_INIT_NORMAL, extraDriverData) != FMOD_OK) { return false; }
		return true;
	}
	void Audio::ShutDown()
	{
		delete audio; audio = nullptr;
		delete extraDriverData; extraDriverData = nullptr;
		delete tempSound; tempSound = nullptr;
		sounds.clear();
	}

	void Audio::CreateSound(const char* fileName)
	{
		audio->createSound(fileName, FMOD_DEFAULT, 0, &tempSound);
		sounds.push_back(tempSound);
	}
	void Audio::PlaySound(int soundIndex, bool paused)
	{
		audio->playSound(sounds[soundIndex], 0, paused, nullptr);
	}
	void Audio::Update()
	{
		audio->update();
	}
}