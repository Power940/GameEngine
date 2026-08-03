#pragma once
#include <ctime>
#include <cstdlib>

namespace STR_FALL
{
	inline void SeedRandom() { std::srand(static_cast<unsigned int>(std::time(nullptr))); }

	inline void SeedRandom(unsigned int seed) { std::srand(seed); }

	inline int RandomInt() { return rand(); }

	inline int RandomInt(int max) { return rand() % max; }

	inline int RandomInt(int max, int min) { return min + rand() % (max - min + 1); }

	inline float RandomFloat() { return rand() / static_cast<float>(RAND_MAX); }

	inline float RandomFloat(float max) { return rand() / static_cast<float>(RAND_MAX) * max; }

	inline float RandomFloat(float max, float min) { return rand() / static_cast<float>(RAND_MAX) * (max - min) + min; }
}