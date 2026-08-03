#pragma once
#include <StarFallEngine.h>
#include "Ship3D.h"

using namespace STR_FALL;

static Mesh3D markerMesh = Mesh3D(
	{Vector3(0.0f,0.0f,0.82f), Vector3(0.58f,0.0f,0.0f), Vector3(-0.29f,0.5f,0.0f), Vector3(-0.29f,-0.5f,0.0f)},
	Color(),
	{
		1,2,3,
		0,1,2,
		0,1,3,
		0,2,3
	}
);

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