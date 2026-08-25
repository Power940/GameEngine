#pragma once
#include "RendererComponent.h"
#include <Resources/Resource.h>


namespace STR_FALL
{
	class SpriteAnimationRenderer2DComponent : public RendererComponent
	{
	public:
		float m_rot = 0.0f;
		Vector2 m_scale = Vector2(1.0f, 1.0f);
		bool flipH = false;

		CLASS_PROTOTYPE(SpriteAnimationRenderer2DComponent)

		virtual void Draw(Renderer& r) override;
		virtual void Update(float dt) override;
		virtual void Read(const rapidjson::Value& value) override;


	private:
		float m_framesPerSecond = 1.0f;
		bool m_loop = true;
		unsigned int m_frame = 0;
		float m_frameTimer = 0.0f;

		res_t<class TextureFrames> m_textureFrames;
	};
}
