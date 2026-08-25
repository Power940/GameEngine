#pragma once
#include <box2d/id.h>


namespace STR_FALL
{
	class Physics
	{
	public:
		Physics() = default;

		bool Initialize();
		void Shutdown();

		void Update(float dt);

	private:
		b2WorldId m_worldId;
	};
}
