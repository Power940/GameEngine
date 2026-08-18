#pragma once
#include "RendererComponent.h"
#include "Resource.h"
#include "Texture.h"
#include "Renderer.h"
#include "Factory.h"

namespace STR_FALL
{
	class SpriteRendererComponent : public RendererComponent
	{
	public:
		res_t<Texture> m_texture;

		CLASS_PROTOTYPE(SpriteRendererComponent)

		virtual void Draw(class Renderer& r) override
		{
			r.RenderTexture(m_texture.get(), )
		}

		virtual void Read(const rapidjson::Value& value) override
		{

		}
	};

	FACTORY_REG(SpriteRendererComponent)
}