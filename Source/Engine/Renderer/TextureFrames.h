#pragma once
#include <Math/Structs.h>
#include "Renderer.h"
#include "Texture.h"
#include <Resources/Resource.h>
#include <string>


namespace STR_FALL
{
	class TextureFrames : public Resource
	{
	public:
		bool Load(const std::string& filename, class Renderer& r);
		Rect2D GetFrameRect(unsigned int frame);

	private:
		int m_columns = 0;
		int m_rows = 0;
		int m_startFrame = 0;
		int m_totalFrames = 0;

		Vector2 m_cellSize = Vector2();
		res_t<Texture> m_texture;
	};
}