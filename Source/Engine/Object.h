#pragma once
#include <string>
#include "Structs.h"
#include "Renderer.h"
#include "Mesh.h"
#include <unordered_set>

namespace STR_FALL
{
	class Scene;

	struct ObjectDesc
	{
		std::string m_name = "";
		std::unordered_set<std::string> m_tags = {};
		Scene* m_scene = nullptr;
		Transform3D m_transform = Transform3D();
		res_t<MultiMesh3D> m_baseMesh;
		res_t<Texture> m_texture;
		BitMaskInt m_collisionLayer;
		BitMaskInt m_collisionMask;
	};

	struct Object
	{ friend Scene;

	public:
		float m_radius = 0.0f;

	protected:
		inline void UPDATE_MESH(MultiMesh3D& toUpdate)
		{
			toUpdate *= m_transform.m_scale;
			toUpdate *= m_transform.m_rotMat;
			toUpdate += m_transform.m_pos;

			m_radius = toUpdate.GetRadius(m_transform.m_pos);
		}

	public:
		std::string m_name;
		std::unordered_set<std::string> m_tags;
		Scene* m_scene = nullptr;
		bool m_toBeFreed = false;

		Transform3D m_transform;
		res_t<MultiMesh3D> m_baseMesh;
		MultiMesh3D m_mesh;
		res_t<Texture> m_texture;
		BitMaskInt m_collisionLayer;
		BitMaskInt m_collisionMask;

		Vector3 m_vel = Vector3();


		inline Object(const ObjectDesc& desc) : m_name(desc.m_name), m_tags(desc.m_tags), m_scene(desc.m_scene), m_transform(desc.m_transform), m_baseMesh(desc.m_baseMesh), m_mesh(MultiMesh3D()), m_collisionLayer(desc.m_collisionLayer), m_collisionMask(desc.m_collisionMask) { m_mesh = *desc.m_baseMesh; UPDATE_MESH(m_mesh); }

		virtual void Update(float dt) {}
		virtual void Draw(Renderer& r) const {}
		virtual void OnCollision(Object* other) {}

		inline Transform3D GetTransform() const { return m_transform; }
		void SetTransform(const Transform3D& transform)
		{
			m_transform = transform;
			m_mesh = *m_baseMesh;
			UPDATE_MESH(m_mesh);
		}
		void SetBaseMesh(const res_t<MultiMesh3D>& mesh) { m_baseMesh = mesh; m_mesh = *mesh; UPDATE_MESH(m_mesh); }

		void SetTransformPos(const Vector3& pos)
		{
			m_mesh += (pos - m_transform.m_pos);
			m_transform.m_pos = pos;
		}
		void IncrementTransformPos(const Vector3& pos)
		{
			m_transform.m_pos += pos;
			m_mesh += pos;
		}
		void SetTransformScale(const Vector3& scale)
		{
			m_transform.m_scale = scale;
			m_mesh = *m_baseMesh;
			UPDATE_MESH(m_mesh);
		}
		void IncrementTransformScale(const Vector3& scale)
		{
			m_transform.m_scale += scale;
			m_mesh = *m_baseMesh;
			UPDATE_MESH(m_mesh);
		}
		void SetTransformRotation(const Matrix3& rot)
		{
			m_transform.m_rotMat = rot;
			m_mesh = *m_baseMesh;
			UPDATE_MESH(m_mesh);
		}
	};
}