#pragma once
#include "Object.h"

namespace STR_FALL
{
	class GameObject;

	class Component : public Object
	{
	public:
		GameObject* m_owner = nullptr;

		Component() = default;
		virtual ~Component() = default;

		virtual void Start() {}
		virtual void Destroyed() {}
		virtual void Update(float dt) {}
	};
}