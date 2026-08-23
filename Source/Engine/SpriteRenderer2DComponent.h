#pragma once
#include "RendererComponent.h"
#include "Resource.h"
#include "Texture.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "StarFallEngine.h"

namespace STR_FALL
{
	class SpriteRenderer2DComponent : public RendererComponent
	{
	public:
		res_t<Texture> m_texture;
		Vector2* m_pos;
		float* m_rot;
		Vector2* m_scale;
		bool* flipH;


		CLASS_PROTOTYPE(SpriteRenderer2DComponent)

		virtual void Draw(class Renderer& r) override
		{
			r.RenderTexture(m_texture.get(), m_pos->m_x, m_pos->m_y, *m_rot, m_scale->m_x, m_scale->m_y, *flipH);
		}

		virtual void Read(const rapidjson::Value& value) override
		{
			RendererComponent::Read(value);

			std::string m_textureFilePath;
			JSON_READ(value, m_textureFilePath);
			if (!m_textureFilePath.empty())
			{
				ResourceManager::ResManager().GetWithID<Texture>(m_textureFilePath.c_str(), m_textureFilePath.c_str(), STR_Engine::m_renderer);
			}
		}
	};

	FACTORY_REG(SpriteRenderer2DComponent)
}