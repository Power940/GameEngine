#pragma once
#include <vector>
#include "Resource.h"
#include "Types/Structs.h"
#include "Types/Texture.h"
#include "Renderer.h"

namespace STR_FALL
{
	struct Particle2D
	{
		bool m_active = false;
		float m_lifespan = 1.0f;

		Vector2 m_position;
		Vector2 m_velocity;
		res_t<Texture> m_texture;
	};


	class ParticleSystem2D
	{
	private:
		std::vector<Particle2D> m_particles;

		Particle2D* GetFreeParticle();

	public:
		ParticleSystem2D() = default;

		bool Initialize(size_t poolSize = 1000);
		void Shutdown();

		void Update(float dt);
		void Draw(Renderer& r);

		void AddParticle(const Particle2D& particle);
	};
}