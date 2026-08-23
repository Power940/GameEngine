#pragma once
#include <StarFallEngine.h>
#include <MeshRenderer3DComponent.h>
#include <utility>
#include <memory>
#include <Factory.h>
#include "Bullet.h"

using namespace STR_FALL;

struct Ship3D : public GameObject
{
	Camera3D m_cam = Camera3D::Empty;
	float m_forceStrength = 0.0f;
	float m_maxVel = 0.0f;

	float m_force = 0.0f;
	Vector3 m_dir = Vector3(0.0f, 0.0f, 1.0f);
	Vector3 m_accel = Vector3();


	Ship3D() = default;
	CLASS_PROTOTYPE(Ship3D)

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

		GetComponent<MeshRenderer3DComponent>()->UpdateMesh(m_transform);

		if (STR_Engine::m_input.GetKeyPressed(Input::VK_SPACE))
		{
			Shoot();
		}
	}

	void Shoot()
	{
		std::unique_ptr<Bullet> bullet = Factory::Instance().Create<Bullet>("BulletPrototype");
		bullet->m_transform = m_transform;
		bullet->m_dir = m_dir;
		m_scene->AddObject(std::move(bullet));

		STR_Engine::m_audio.PlaySound("shoot");
	}


	virtual void Read(const rapidjson::Value& value) override
	{
		GameObject::Read(value);

		JSON_READ(value, m_cam);
		JSON_READ(value, m_forceStrength);
		JSON_READ(value, m_maxVel);
	}
};

FACTORY_REG(Ship3D);