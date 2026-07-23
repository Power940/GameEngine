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

struct Marker : public Object<Transform3D, Mesh3D>
{
	const Ship3D* m_player;
	bool m_canMove = false;

	Marker(const ObjectDesc<Transform3D, Mesh3D>& desc) :
		Object(desc), m_player(m_scene->GetObjectName<Ship3D>("player")) { }

	void Update(float dt) override
	{
		if (m_canMove)
		{
			Vector3 dir = Vector3(m_transform.m_pos, m_player->GetTransform().m_pos);
			dir.Normalize();
			IncrementTransformPos(dir * dt);
		}
	}

	void Draw(Renderer& r, const Camera3D& c = Camera3D::Empty) const override
	{
		r.SetColor(m_mesh.m_color);
		r.Render3DCustomOutline(c, m_mesh.m_points, m_mesh.m_indices);
	}
};