#include "pch.h"
#include "SpriteAnimationRenderer2DComponent.h"
#include <Core/Factory.h>
#include <Resources/ResourceManager.h>
#include <Renderer/TextureFrames.h>
#include "StarFallEngine.h"
#include <Math/Structs.h>
#include <Renderer/Renderer.h>

namespace STR_FALL
{
	FACTORY_REG(SpriteAnimationRenderer2DComponent)

	void SpriteAnimationRenderer2DComponent::Draw(Renderer& r)
	{
		if (!m_textureFrames) { return; }

		Transform3D transform = m_owner->m_transform;
		r.RenderTexture(
			m_textureFrames->GetTexture().get(),
			m_textureFrames->GetFrameRect(m_frame),
			transform.m_pos.m_x,
			transform.m_pos.m_y,
			m_rot,
			transform.m_scale.m_x,
			transform.m_scale.m_y
		);
	}

	void SpriteAnimationRenderer2DComponent::Update(float dt)
	{
		m_frameTimer += dt;
		float frameTime = 1.0f / m_framesPerSecond;
		while (m_frameTimer >= frameTime)
		{
			m_frame++;
			if (m_loop)
			{
				m_frame %= m_textureFrames->GetTotalFrames();
			}
			else if (m_frame >= m_textureFrames->GetTotalFrames() - 1)
			{
				m_frame = m_textureFrames->GetTotalFrames() - 1;
			}

			m_frameTimer -= frameTime;
		}
	}

	void SpriteAnimationRenderer2DComponent::Read(const rapidjson::Value& value)
	{
		RendererComponent::Read(value);

		JSON_READ(value, m_framesPerSecond);
		JSON_READ(value, m_loop);

		std::string m_textureFrameName;
		JSON_READ(value, m_textureFrameName);

		if (!m_textureFrameName.empty())
		{
			m_textureFrames = ResourceManager::ResManager().GetWithID<TextureFrames>(m_textureFrameName.c_str(), m_textureFrameName.c_str(), STR_Engine::m_renderer);
			if (!m_textureFrames)
			{
				std::cerr << "Could not load texture frames: " << m_textureFrameName << std::endl;
			}
		}
	}
}