#include "Scene.h"
#include "Object.h"

namespace STR_FALL
{
	void Scene::Update(float dt)
	{
		for (BaseObject*& object : m_objects) { object->Update(dt); }
	}

	void Scene::Draw(Renderer& r, const Camera3D& c)
	{
		for (BaseObject*& object : m_objects) { object->Draw(r, c); }
	}
}