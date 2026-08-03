#pragma once
#include <vector>
#include <memory>
#include "Object.h"

namespace STR_FALL
{
	class Scene
	{
	private:
		std::vector<std::unique_ptr<Object>> m_objects;
		std::vector<std::unique_ptr<Object>> m_pendingObjects;
		bool m_safeToAddObject = true;

	public:
		class Game* m_game = nullptr;

		inline void AddObject(std::unique_ptr<Object> object)
		{
			if (object->m_scene == nullptr) { object->m_scene = this; }

			if (m_safeToAddObject) { m_objects.push_back(std::move(object)); }
			else { m_pendingObjects.push_back(std::move(object)); }
		}
		inline Object* GetObjectIndex(const int element) const { return m_objects[element].get(); }

		template<typename T>
		inline T* GetObjectName(const std::string& name)
		{
			for (auto& object : m_objects)
			{
				T* objectT = dynamic_cast<T*>(object.get());
				if (objectT != nullptr && objectT->m_name == name) { return objectT; }
			}
			return nullptr;
		}

		void Update(float dt);
		void Draw(Renderer& r);

		void UpdateCollisions();

		void RemoveAllObjects() { m_objects.clear(); m_pendingObjects.clear(); }
	};
}