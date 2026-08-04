#pragma once
#include <SDL3_image/SDL_image.h>
#include <string>
#include <iostream>
#include "Structs.h"
#include "Renderer.h" 

namespace STR_FALL
{
	class Texture
	{
	friend class Renderer;

	public:
		Texture() = default;
		~Texture();

		bool Load(const std::string& filename, Renderer& renderer);

		Vector2 GetSize();

	private:
		SDL_Texture* m_texture = nullptr;
	};
}