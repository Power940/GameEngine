#pragma once
#include "RendererComponent.h"
#include "Resources/Resource.h"
#include "Renderer/Texture.h"
#include "Renderer/Renderer.h"
#include "Resources/ResourceManager.h"
#include "StarFallEngine.h"

namespace STR_FALL
{
	class SpriteRenderer2DComponent : public RendererComponent
	{
	public:
		res_t<Texture> m_texture;
		float m_rot = 0.0f;
		Vector2 m_scale = Vector2(1.0f, 1.0f);
		bool flipH = false;


		CLASS_PROTOTYPE(SpriteRenderer2DComponent)

		virtual void Draw(class Renderer& r) override
		{
			r.RenderTexture(m_texture.get(), m_owner->m_transform.m_pos.m_x, m_owner->m_transform.m_pos.m_y, m_rot, m_scale.m_x, m_scale.m_y, flipH);
		}

		virtual void Read(const rapidjson::Value& value) override
		{
			RendererComponent::Read(value);

			std::string m_textureFilePath;
			JSON_READ(value, m_textureFilePath);
			if (!m_textureFilePath.empty())
			{
				m_texture = ResourceManager::ResManager().GetWithID<Texture>(m_textureFilePath.c_str(), m_textureFilePath.c_str(), STR_Engine::m_renderer);
			}
		}
	};

	FACTORY_REG(SpriteRenderer2DComponent)
}