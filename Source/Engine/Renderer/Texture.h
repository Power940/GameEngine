#pragma once
#include <SDL3_image/SDL_image.h>
#include <string>
#include <iostream>
#include "Math/Structs.h"
#include "Renderer.h" 
#include "Resources/Resource.h"

namespace STR_FALL
{
	class Texture : public Resource
	{
	friend class Renderer;

	public:
		Texture() = default;
		~Texture();

		bool Load(const std::string& filename, Renderer& renderer);

		SDL_Texture* m_texture = nullptr;
		Vector2 m_size = Vector2();
	};
}