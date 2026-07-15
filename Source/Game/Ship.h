#pragma once
#include <Object.h>
#include <StarFallEngine.h>

using namespace STR_FALL;

struct Ship : public Object<Transform2D, Mesh2D>
{
	Color m_color;
	Vector2 m_dir = Vector2(1.0f, 0.0f);
	Vector2 m_accel = Vector2();

	float m_forceStrength;
	float m_force = 0.0f;
	float m_maxVel;

	Ship(const Transform2D& t, const Color& c, const float fs, const float mv) :
		Object(t, SpaceShip), m_color(c), m_forceStrength(fs), m_maxVel(mv) {}

	virtual void Update(float dt)
	{
		IncrementTransformRotation(
			(g_engine.m_input.GetKeyDown(SDL_SCANCODE_A) - g_engine.m_input.GetKeyDown(SDL_SCANCODE_D)) * dt * 3.0f
		);

		m_force = g_engine.m_input.GetKeyDown(SDL_SCANCODE_W) * m_forceStrength;

		m_dir = Vector2(1.0f, 0.0f) * m_transform.GetRotationMatrix();
		m_accel = m_dir * m_force;
		m_vel += m_accel * dt;

		m_vel.ClampMag(0, m_maxVel);
		IncrementTransformPos(m_vel * dt);
		m_vel *= std::pow(0.95f, dt);

		#pragma region Wrap logic
		if (g_engine.m_renderer.GetSreenWidth() < m_transform.m_pos.m_x)
		{
			SetTransformPos(Vector2(m_transform.m_pos.m_x - g_engine.m_renderer.GetSreenWidth(), m_transform.m_pos.m_y));
		}
		if (m_transform.m_pos.m_x < 0)
		{
			SetTransformPos(Vector2(m_transform.m_pos.m_x + g_engine.m_renderer.GetSreenWidth(), m_transform.m_pos.m_y));
		}
		if (g_engine.m_renderer.GetSreenHeight() < m_transform.m_pos.m_y)
		{
			SetTransformPos(Vector2(m_transform.m_pos.m_x, m_transform.m_pos.m_y - g_engine.m_renderer.GetSreenHeight()));
		}
		if (m_transform.m_pos.m_y < 0)
		{
			SetTransformPos(Vector2(m_transform.m_pos.m_x, m_transform.m_pos.m_y + g_engine.m_renderer.GetSreenHeight()));
		}
		#pragma endregion
	}

	void Draw(Renderer& r, const Camera3D& c) const override
	{
		r.SetColor(m_mesh.m_color);
		r.RenderCustomOutline(m_mesh.m_points);
	}
};