#pragma once
#include <StarFallEngine.h>
#include "Ship3D.h"

using namespace STR_FALL;

struct Marker : public Object
{
	const Ship3D* m_player;
	const bool m_canBeHit;


	Marker(const ObjectDesc& desc, bool canBeHit) :
		Object(desc), m_player(m_scene->GetObjectName<Ship3D>("player")), m_canBeHit(canBeHit) { }

	void Update(float dt) override { }

	void Draw(Renderer& r) const override
	{
		r.SetColor(m_mesh[0].m_color);
		r.Render3DCustomOutline(m_mesh[0].m_points, m_mesh[0].m_indices);
	}
};