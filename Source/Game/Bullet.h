#pragma once
#include <StarFallEngine.h>

using namespace STR_FALL;

static Mesh3D bulletMesh = Mesh3D(
	{ Vector3(0.0f,0.0f,0.25f), Vector3(0.01f,0.0f,-0.25f), Vector3(-0.01f,0.0f,-0.25f) },
	Color(),
	{ 0,1,2 }
);

struct Bullet : public Object
{
	Vector3 m_dir;


	Bullet(const ObjectDesc& desc, const Vector3& dir) :
		Object(desc), m_dir(dir) { }

	void Update(float dt) override
	{
		IncrementTransformPos(m_dir * dt * 500);
	}

	void OnCollision(Object* other) override
	{
		if (other->m_tags.contains("marker"))
		{
			other->m_toBeFreed = true;
			m_toBeFreed = true;
		}
	}

	void Draw(Renderer& r) const override
	{
		r.SetColor(m_mesh[0].m_color);
		r.Render3DCustomOutline(m_mesh[0].m_points, m_mesh[0].m_indices);
	}
};