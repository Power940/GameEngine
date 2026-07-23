#include "Scene.h"
#include "Object.h"

namespace STR_FALL
{
	void Scene::Update(float dt)
	{
		m_safeToAddObject = false;
		for (BaseObject*& object : m_objects) { object->Update(dt); }
		m_safeToAddObject = true;

		// TODO: add this after fix to get object search
		//std::erase_if(m_objects, [](auto object) { return object->isDestroed; });

		m_objects.insert(m_objects.end(), m_pendingObjects.begin(), m_pendingObjects.end());
		m_pendingObjects.clear();
	}

	void Scene::Draw(Renderer& r, const Camera3D& c)
	{
		for (BaseObject*& object : m_objects) { object->Draw(r, c); }
	}
}