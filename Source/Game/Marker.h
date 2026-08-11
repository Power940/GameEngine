#pragma once
#include <StarFallEngine.h>
#include "Ship3D.h"

using namespace STR_FALL;

struct Marker : public GameObject
{
	const Ship3D* m_player;
	const bool m_canBeHit;


	Marker(const GameObjectDesc& desc, bool canBeHit) :
		GameObject(desc), m_player(m_scene->GetObjectName<Ship3D>("player")), m_canBeHit(canBeHit) { }

	void Update(float dt) override { }

	void Draw(Renderer& r) const override
	{
		r.Render3DCustomTexture(m_mesh[0].m_points, m_mesh[0].m_indices, m_mesh[0].m_texture.get());
	}
};