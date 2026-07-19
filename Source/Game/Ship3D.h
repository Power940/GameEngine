#pragma once
#include <Object.h>
#include <StarFallEngine.h>

using namespace STR_FALL;

struct Ship3D : public Object<Transform3D, Mesh3D>
{
	Color m_color;
	Vector3 m_dir = Vector3(0.0f, 0.0f, 1.0f);
	Vector3 m_accel = Vector3();
	Camera3D m_cam;

	float m_forceStrength;
	float m_force = 0.0f;
	float m_maxVel;

	Ship3D(const Transform3D& t, const Camera3D& cam, const float fs, const float mv) :
		Object(t, Rect3DMesh), m_cam(cam), m_forceStrength(fs), m_maxVel(mv) {
	}

	virtual void Update(float dt)
	{
		IncrementTransformRotation(
			Vector3(g_engine.m_input.GetKeyDown(SDL_SCANCODE_W) - g_engine.m_input.GetKeyDown(SDL_SCANCODE_S), 0.0f, g_engine.m_input.GetKeyDown(SDL_SCANCODE_A) - g_engine.m_input.GetKeyDown(SDL_SCANCODE_D)) * dt * 3.0f
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
		m_cam.m_transform.m_pos += (m_transform.GetRotationMatrix().Up() * -10.0f) + (m_transform.GetRotationMatrix().Forward() * -10.0f);
		m_cam.m_rotMat = m_transform.GetRotationMatrix();
	}

	void Draw(Renderer& r, const Camera3D& c = Camera3D::Empty) const override
	{
		r.SetColor(m_mesh.m_color);
		g_engine.m_renderer.Render3DCustomOutline(m_cam, m_mesh.m_points, m_mesh.m_indices);
	}
};