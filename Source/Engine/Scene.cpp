#include "Scene.h"
#include "Object.h"

namespace STR_FALL
{
	void Scene::Update(float dt)
	{
		m_safeToAddObject = false;
		for (auto& object : m_objects) { object->Update(dt); }
		m_safeToAddObject = true;

		UpdateCollisions();

		std::erase_if(m_objects, [](auto& object) { return object->m_toBeFreed; });

		// TODO look into this
		// std::move_iterator
		//m_objects.insert(m_objects.end(), m_pendingObjects.begin(), m_pendingObjects.end());
		for (auto& object : m_pendingObjects)
		{
			m_objects.push_back(std::move(object));
		}
		m_pendingObjects.clear();
	}

	void Scene::Draw(Renderer& r)
	{
		for (auto& object : m_objects) { object->Draw(r); }
	}

	void Scene::UpdateCollisions()
	{
		float dist = -1.0f;
		Object* ObjectA;
		Object* ObjectB;

		for (int indexA = 0; indexA < m_objects.size(); indexA++)
		{
			ObjectA = m_objects[indexA].get();
			if (ObjectA->m_toBeFreed) { continue; }

			for (int indexB = indexA + 1; indexB < m_objects.size(); indexB++)
			{
				ObjectB = m_objects[indexB].get();
				if (ObjectB->m_toBeFreed) { continue; }

				if (ObjectA->m_collisionMask.AnyMatch(ObjectB->m_collisionLayer))
				{
					dist = (ObjectA->m_transform.m_pos - ObjectB->m_transform.m_pos).Magnitude();

					if (dist <= ObjectA->m_radius + ObjectB->m_radius)
					{
						ObjectA->OnCollision(ObjectB);
						std::cout << ObjectA->m_name + " a -> b " + ObjectB->m_name << std::endl;
					}

					// add SAT later if you feel like it (in an else case)
				}

				if (ObjectB->m_collisionMask.AnyMatch(ObjectA->m_collisionLayer))
				{
					dist = (ObjectA->m_transform.m_pos - ObjectB->m_transform.m_pos).Magnitude();

					if (dist <= ObjectA->m_radius + ObjectB->m_radius)
					{
						ObjectB->OnCollision(ObjectA);
					}

					// add SAT later if you feel like it (in an else case)
				}
			}
		}
	}
}