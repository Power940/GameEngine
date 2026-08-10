#pragma once
#include <StarFallEngine.h>
#include "Bullet.h"
#include "Assets.h"

using namespace STR_FALL;

struct Ship3DDesc : public ObjectDesc
{
	float m_forceStrength = 0.0f;
	float m_maxVel = 0.0f;
	Camera3D m_cam;
};

struct Ship3D : public Object
{
	Vector3 m_dir = Vector3(0.0f, 0.0f, 1.0f);
	Vector3 m_accel = Vector3();
	Camera3D m_cam;

	float m_forceStrength;
	float m_force = 0.0f;
	float m_maxVel;


	Ship3D(const Ship3DDesc& desc) : Object(desc), m_cam(desc.m_cam), m_forceStrength(desc.m_forceStrength), m_maxVel(desc.m_maxVel) {}

	void Update(float dt) override
	{
		float pitch = STR_Engine::Get().m_input.GetKeyDiff(Input::VK_W, Input::VK_S) * dt * 3.0f;
		float roll = STR_Engine::Get().m_input.GetKeyDiff(Input::VK_A, Input::VK_D) * dt * 3.0f;
		float yaw = STR_Engine::Get().m_input.GetKeyDiff(Input::VK_Q, Input::VK_E) * dt * 3.0f;
		SetTransformRotation(m_transform.m_rotMat * Matrix3::RotationX(pitch) * Matrix3::RotationZ(roll) * Matrix3::RotationY(yaw));

		m_dir = m_transform.m_rotMat.Forward().Normalize();
		m_force = STR_Engine::Get().m_input.GetKeyDown(Input::VK_UP) * m_forceStrength;
		m_accel = m_dir * m_force;
		m_vel += m_accel * dt;

		m_vel.ClampMag(0, m_maxVel);
		IncrementTransformPos(m_vel * dt);
		m_vel *= std::pow(0.95f, dt);
		if (STR_Engine::Get().m_input.GetKeyDown(Input::VK_X))
			m_vel = Vector3();

		m_cam.m_transform = m_transform;
		m_cam.m_transform.m_pos += (m_transform.m_rotMat.Up() * -20.0f) + (m_transform.m_rotMat.Forward() * -30.0f);
		m_cam.m_transform.m_rotMat = m_transform.m_rotMat;

		if (STR_Engine::m_input.GetKeyPressed(Input::VK_SPACE))
		{
			Shoot();
		}
	}

	void Draw(Renderer& r) const override
	{
		r.SetColor(m_mesh[0].m_color);
		r.Render3DCustomOutline(m_mesh[0].GetPoints(), m_mesh[0].m_indices);
		r.SetColor(m_mesh[1].m_color);
		r.Render3DCustomOutline(m_mesh[1].GetPoints(), m_mesh[1].m_indices);
		if (STR_Engine::Get().m_input.GetKeyDown(SDL_SCANCODE_UP))
		{
			r.SetColor(m_mesh[2].m_color);
			Mesh3D flame = m_mesh[2];
			flame.GetPoints()[1].m_z += RandomFloat(2.5f, -2.5f);
			r.Render3DCustomOutline(flame.GetPoints(), flame.m_indices);
		}
	}

	void Shoot()
	{
		ObjectDesc bulletDesc;
		bulletDesc.m_transform = m_transform;
		bulletDesc.m_baseMesh = std::make_shared<MultiMesh3D>(bulletMesh);
		bulletDesc.m_name = "player bullet";
		bulletDesc.m_tags = { "bullet" };
		bulletDesc.m_scene = m_scene;
		bulletDesc.m_collisionLayer = BitMaskInt(1);
		bulletDesc.m_collisionMask = BitMaskInt(2);
		m_scene->AddObject(std::move(std::make_unique<Bullet>(bulletDesc, m_dir)));

		STR_Engine::m_audio.PlaySound("shoot");
	}
};