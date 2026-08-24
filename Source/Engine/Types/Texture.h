#pragma once
#include <SDL3_image/SDL_image.h>
#include <string>
#include <iostream>
#include "Structs.h"
#include "Systems/Renderer.h" 
#include "Systems/Resource.h"

namespace STR_FALL
{
	class Texture : public Resource
	{
	friend class Renderer;

	public:
		Texture() = default;
		~Texture();

		bool Load(const std::string& filename, Renderer& renderer);

	private:
		SDL_Texture* m_texture = nullptr;
		Vector2 m_size = Vector2();
	};
}