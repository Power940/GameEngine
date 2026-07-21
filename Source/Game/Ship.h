#pragma once
#include <StarFallEngine.h>

using namespace STR_FALL;

static MultiMesh2D SpaceShip = MultiMesh2D({
	Mesh2D({Vector2(-0.5f, 0.5f), Vector2(0.5f, 0.0f), Vector2(-0.5f,-0.5f), Vector2(-0.25f,0.0f)}, Color()), // body
	Mesh2D({Vector2(0.0f, 0.2f), Vector2(0.0f, -0.2f), Vector2(0.4f, 0.0f)}, Color(0.0f, 0.0f, 1.0f)), // window
	Mesh2D({Vector2(-1.0f, 0.0f), Vector2(-0.5f, 0.2f), Vector2(-0.35f, 0.0f), Vector2(-0.5f, -0.2f)}, Color(1.0f, 1.0f, 0.5f)) // flame
	});

struct ShipDesc : public ObjectDesc<Transform2D, MultiMesh2D>
{
	float m_forceStrength;
	float m_maxVel;
};

struct Ship : public Object<Transform2D, MultiMesh2D>
{
	Vector2 m_dir = Vector2(1.0f, 0.0f);
	Vector2 m_accel = Vector2();

	float m_forceStrength;
	float m_force = 0.0f;
	float m_maxVel;

	Ship(const ShipDesc& desc) :
		Object(desc), m_forceStrength(desc.m_forceStrength), m_maxVel(desc.m_maxVel) {}

	void Update(float dt) override 
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
		if (g_engine.m_input.GetKeyDown(SDL_SCANCODE_SPACE))
			m_vel = Vector2();

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

	void Draw(Renderer& r, const Camera3D& c = Camera3D::Empty) const override
	{
		r.SetColor(m_mesh[0].m_color);
		r.RenderCustomOutline(m_mesh[0].m_points);
		r.SetColor(m_mesh[1].m_color);
		r.RenderCustomOutline(m_mesh[1].m_points);
		if (g_engine.m_input.GetKeyDown(SDL_SCANCODE_W))
		{
			r.SetColor(m_mesh[2].m_color);
			r.RenderCustomOutline(m_mesh[2].m_points);
		}
	}
};