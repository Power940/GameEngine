#pragma once
#include <vector>
#include "Object.h"

namespace STR_FALL
{
	class Scene
	{
	private:
		std::vector<BaseObject*> m_objects;
		std::vector<BaseObject*> m_pendingObjects;
		bool m_safeToAddObject = true;

	public:
		template<typename T, typename M>
		requires CompatibleObject<T, M>
		inline void AddObject(Object<T, M>* object)
		{
			if (m_safeToAddObject) { m_objects.push_back(object); }
			else { m_pendingObjects.push_back(object); }

			if (object->m_scene == nullptr) { object->m_scene = this; }
		}
		inline BaseObject* GetObjectIndex(const int element) const { return m_objects[element]; }

		template<typename T>
		inline T* GetObjectName(const std::string& name)
		{
			for (BaseObject* object : m_objects)
			{
				T* objectT = dynamic_cast<T*>(object);
				if (objectT != nullptr && objectT->m_name == name) { return dynamic_cast<T*>(object); }
			}
			return nullptr;
		}

		void Update(float dt);
		void Draw(Renderer& r, const Camera3D& c = Camera3D::Empty);
	};
}