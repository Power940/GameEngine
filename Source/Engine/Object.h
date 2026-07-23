#pragma once
#include <concepts>
#include <utility>
#include <string>
#include "Structs.h"
#include "Renderer.h"
#include "Mesh.h"
#include "Constants.h"

namespace STR_FALL
{
	class Scene;

	template<typename T, typename M>
	concept CompatibleObject =
		(std::same_as<T, Transform2D> && (std::same_as<M, Mesh2D> || std::same_as<M, MultiMesh2D>)) ||
		(std::same_as<T, Transform3D> && (std::same_as<M, Mesh3D> || std::same_as<M, MultiMesh3D>));



	struct BaseObjectDesc
	{
		std::string m_name;
		std::vector<std::string> m_tags;
		Scene* m_scene = nullptr;
	};

	struct BaseObject
	{
	protected:
		std::string m_name;
		std::vector<std::string> m_tags;
		Scene* m_scene = nullptr;

		inline BaseObject(const BaseObjectDesc& desc) : m_name(desc.m_name), m_tags(desc.m_tags), m_scene(desc.m_scene) {}

	public:
		friend Scene;
		virtual void Update(float dt) = 0;
		virtual void Draw(Renderer& r, const Camera3D& c = Camera3D::Empty) const = 0;
	};

	template<typename T, typename M> requires CompatibleObject<T, M>
	struct ObjectDesc : public BaseObjectDesc
	{
		T m_transform;
		M m_baseMesh;
	};

	template<typename T, typename M> requires CompatibleObject<T, M>
	struct Object : public BaseObject
	{
	protected:
		T m_transform;
		M m_baseMesh;
		M m_mesh;

		inline void UPDATE_MESH()
		{
			m_mesh *= m_transform.m_scale;
			m_mesh *= m_transform.GetRotationMatrix();
			m_mesh += m_transform.m_pos;
		}

	public:
		decltype(std::declval<T>().m_pos) m_vel = decltype(std::declval<T>().m_pos)();

		inline Object(const ObjectDesc<T,M>& desc):
			m_transform(desc.m_transform),
			m_baseMesh(desc.m_baseMesh),
			m_mesh(desc.m_baseMesh),
			BaseObject(desc)
		{ UPDATE_MESH(); }

		virtual void Update(float dt) = 0;
		virtual void Draw(Renderer& r, const Camera3D& c = Camera3D::Empty) const = 0;

		inline T GetTransform() const { return m_transform; }
		void SetTransform(const T& transform)
		{
			m_transform = transform;
			m_mesh = m_baseMesh;
			UPDATE_MESH();
		}
		inline M GetBaseMesh() const { return m_baseMesh; }
		inline M GetMesh() const { return m_mesh; }
		void SetBaseMesh(const M& mesh) { m_baseMesh = mesh; m_mesh = mesh; UPDATE_MESH(); }

		void SetTransformPos(const decltype(std::declval<T>().m_pos)& pos)
		{
			m_mesh += (pos - m_transform.m_pos);
			m_transform.m_pos = pos;
		}
		void IncrementTransformPos(const decltype(std::declval<T>().m_pos)& pos)
		{
			m_transform.m_pos += pos;
			m_mesh += pos;
		}
		void SetTransformScale(const decltype(std::declval<T>().m_scale)& scale)
		{
			m_transform.m_scale = scale;
			m_mesh = m_baseMesh;
			UPDATE_MESH();
		}
		void IncrementTransformScale(const decltype(std::declval<T>().m_scale)& scale)
		{
			m_transform.m_scale += scale;
			m_mesh = m_baseMesh;
			UPDATE_MESH();
		}
		void SetTransformRotation(const decltype(std::declval<T>().m_rot)& rot)
		{
			m_transform.SetRotation(rot);
			m_mesh = m_baseMesh;
			UPDATE_MESH();
		}
		void IncrementTransformRotation(const decltype(std::declval<T>().m_rot)& rot)
		{
			m_transform.SetRotation(m_transform.m_rot + rot);
			m_mesh = m_baseMesh;
			UPDATE_MESH();
		}
	};
}