#pragma once
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <iostream>

namespace STR_FALL
{
	struct Font
	{
	public:
		Font() = default;
		~Font();

		bool Load(const std::string& name, float fontSize);

	private:
		friend struct Text;

		TTF_Font* m_ttfFont = nullptr;
	};
}