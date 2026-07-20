#pragma once
#include <Object.h>
#include <StarFallEngine.h>

using namespace STR_FALL;

static MultiMesh3D SpaceShip3D = MultiMesh3D({
	Mesh3D(
		{Vector3(0.0f, 0.0f, 0.5f), Vector3(0.5f, 0.0f, -0.5f), Vector3(-0.5f, 0.0f, -0.5f), Vector3(0.0f, 0.0f, -0.25f), Vector3(0.0f, 0.1f, 0.0f), Vector3(0.0f, -0.1f, 0.0f)},
		Color(),
		{
			0,1,5,
			0,1,4,
			0,2,4,
			0,2,5,
			3,2,5,
			3,2,4,
			3,1,4,
			3,1,5
		}
	),
	Mesh3D(
		{Vector3(0.0f,-0.05f,0.25f), Vector3(0.0f,-0.08f,0.1f), Vector3(0.1f,-0.03f,0.15f), Vector3(-0.1f,-0.03f,0.15f)},
		Color(0.0f, 0.0f, 1.0f),
		{
			0,2,1,
			0,3,1
		}
	),
	Mesh3D(
		{Vector3(0.0f,0.0f,-0.4f), Vector3(0.0f,0.0f,-1.0f), Vector3(0.2f,0.0f,-0.6f), Vector3(-0.2f,0.0f,-0.6f), Vector3(0.0f,-0.2f,-0.6f), Vector3(0.0f,0.2f,-0.6f)},
		Color(1.0f, 1.0f, 0.5f),
		{
			0,4,3,
			0,5,3,
			0,2,5,
			0,2,4,
			1,4,3,
			1,5,3,
			1,2,5,
			1,2,4
		}
	)
	});

struct Ship3D : public Object<Transform3D, MultiMesh3D>
{
	Color m_color;
	Vector3 m_dir = Vector3(0.0f, 0.0f, 1.0f);
	Vector3 m_accel = Vector3();
	Camera3D m_cam;

	float m_forceStrength;
	float m_force = 0.0f;
	float m_maxVel;

	Ship3D(const Transform3D& t, const Camera3D& cam, const float fs, const float mv) :
		Object(t, SpaceShip3D), m_cam(cam), m_forceStrength(fs), m_maxVel(mv) {
	}

	void Update(float dt) override
	{
		IncrementTransformRotation(
			Vector3(0.0f, 0.0f, g_engine.m_input.GetKeyDown(SDL_SCANCODE_D) - g_engine.m_input.GetKeyDown(SDL_SCANCODE_A)) * dt * 3.0f
		);
		IncrementTransformRotation(
			Vector3(g_engine.m_input.GetKeyDown(SDL_SCANCODE_W) - g_engine.m_input.GetKeyDown(SDL_SCANCODE_S), 0.0f, 0.0f) * dt * 3.0f
		);

		m_force = g_engine.m_input.GetKeyDown(SDL_SCANCODE_UP) * m_forceStrength;

		m_dir = Vector3(0.0f, 0.0f, 1.0f) * m_transform.GetRotationMatrix();
		m_accel = m_dir * m_force;
		m_vel += m_accel * dt;

		m_vel.ClampMag(0, m_maxVel);
		IncrementTransformPos(m_vel * dt);
		m_vel *= std::pow(0.95f, dt);
		if (g_engine.m_input.GetKeyDown(SDL_SCANCODE_SPACE))
			m_vel = Vector3();

		m_cam.m_transform = m_transform;
		m_cam.m_transform.m_pos += (m_transform.GetRotationMatrix().Up() * -20.0f) + (m_transform.GetRotationMatrix().Forward() * -30.0f);
		m_cam.m_rotMat = m_transform.GetRotationMatrix();
	}

	void Draw(Renderer& r, const Camera3D& c = Camera3D::Empty) const override
	{
		r.SetColor(m_mesh[0].m_color);
		g_engine.m_renderer.Render3DCustomOutline(m_cam, m_mesh[0].m_points, m_mesh[0].m_indices);
		r.SetColor(m_mesh[1].m_color);
		g_engine.m_renderer.Render3DCustomOutline(m_cam, m_mesh[1].m_points, m_mesh[1].m_indices);
		if (g_engine.m_input.GetKeyDown(SDL_SCANCODE_UP))
		{
			r.SetColor(m_mesh[2].m_color);
			Mesh3D flamme = m_mesh[2];
			float flameDelta = RandomFloat(5.0f) - 2.5f;
			flamme.m_points[1].m_z += flameDelta;
			g_engine.m_renderer.Render3DCustomOutline(m_cam, flamme.m_points, flamme.m_indices);
		}
	}
};