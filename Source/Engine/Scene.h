#pragma once
#include <vector>
#include "Object.h"

namespace STR_FALL
{
	class Scene
	{
	private:
		std::vector<BaseObject*> m_objects;

	public:
		template<typename T, typename M>
		requires CompatibleObject<T, M>
		inline void AddObject(Object<T, M>* object) { m_objects.push_back(object); object->m_scene = this; }
		inline BaseObject* GetObjectIndex(const int element) const { return m_objects[element]; }

		template<typename T>
		inline T* GetObjectName(const std::string& name)
		{
			for (BaseObject* object : m_objects)
			{
				T* objectT = dynamic_cast<T*>(object);
				if (objectT && objectT->m_name == name) { return dynamic_cast<T*>(object); }
			}
		}

		void Update(float dt);
		void Draw(Renderer& r, const Camera3D& c = Camera3D::Empty);
	};
}