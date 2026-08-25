#include "pch.h"
#include "RidgidBodyPhysicsComponent.h"
#include <Core/Factory.h>
#include <Math/Structs.h>
#include "PhysicsComponent.h"
#include <Serialization/Json.h>

namespace STR_FALL
{
	FACTORY_REG(RidgidBodyPhysicsComponent)

	void STR_FALL::RidgidBodyPhysicsComponent::ApplyForce(const Vector2& force)
	{
		m_acc = force / m_mass;
	}

	void RidgidBodyPhysicsComponent::SetVelocity(const Vector2& velocity)
	{
		m_vel = velocity;
	}

	Vector2 RidgidBodyPhysicsComponent::GetVelocity()
	{
		return m_vel;
	}

	void RidgidBodyPhysicsComponent::ApplyTorque(float torque)
	{
		m_angAcc += torque / m_mass;
	}

	void RidgidBodyPhysicsComponent::SetAngularVelocity(float angularVelocity)
	{
		m_angVel = angularVelocity;
	}

	float RidgidBodyPhysicsComponent::GetAngularVelocity() const
	{
		return m_angVel;
	}

	void RidgidBodyPhysicsComponent::SetPosition(const Vector2& position)
	{
		m_owner->SetTransformPos(position);
	}

	Vector2 RidgidBodyPhysicsComponent::GetPosition() const
	{
		return m_owner->GetTransform().m_pos;
	}

	void RidgidBodyPhysicsComponent::Update(float dt)
	{
		m_vel += m_acc * dt;
		m_vel *= 1.0f / (1.0f + m_damping * dt);

		m_angVel += m_angAcc * dt;
		m_angVel *= 1.0f / (1.0f + m_angularDamping * dt);

		m_owner->SetTransformPos(m_owner->GetTransform().m_pos + m_vel * dt);
		// TODO add this
		//m_owner->SetTransformRotation();

		m_acc = Vector2();
		m_angAcc = 0.0f;
	}

	void RidgidBodyPhysicsComponent::Read(const rapidjson::Value& value)
	{
		PhysicsComponent::Read(value);

		JSON_READ(value, m_vel);
		JSON_READ(value, m_angVel);
	}
}