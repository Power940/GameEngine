#pragma once
#include "PhysicsComponent.h"
#include <Math/Structs.h>

namespace STR_FALL
{
	class RidgidBodyPhysicsComponent : public PhysicsComponent
	{
	public:
		void ApplyForce(const Vector2& force) override;
		void SetVelocity(const Vector2& velocity) override;
		Vector2 GetVelocity() override;

		void ApplyTorque(float torque) override;
		void SetAngularVelocity(float angularVelocity) override;
		float GetAngularVelocity() const override;

		void SetPosition(const Vector2& position) override;
		Vector2 GetPosition() const override;

		virtual void Update(float dt);
		virtual void Read(const rapidjson::Value& value);

	private:
		Vector2 m_acc = Vector2();
		Vector2 m_vel = Vector2();

		float m_angAcc = 0.0f;
		float m_angVel = 0.0f;
	};
}