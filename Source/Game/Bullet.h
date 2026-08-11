#pragma once
#include <StarFallEngine.h>

using namespace STR_FALL;

struct Bullet : public GameObject
{
	Vector3 m_dir;


	Bullet(const GameObjectDesc& desc, const Vector3& dir) :
		GameObject(desc), m_dir(dir) { }

	void Update(float dt) override
	{
		IncrementTransformPos(m_dir * dt * 500);
	}

	void OnCollision(GameObject* other) override
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