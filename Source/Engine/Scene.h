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
		inline void AddObject(Object<T,M>* object) { m_objects.push_back(object); }
		inline BaseObject* GetObject(const int element) const { return m_objects[element]; }

		void Update(float dt);
		void Draw(Renderer& r, const Camera3D& c = Camera3D::Empty);
	};
}