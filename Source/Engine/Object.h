#pragma once
#include <concepts>
#include <utility>
#include "Structs.h"
#include "Renderer.h"
#include "Mesh.h"
#include "Constants.h"

namespace STR_FALL
{
	template<typename T, typename M>
	concept CompatibleObject = (std::same_as<T, Transform2D> && (std::same_as<M, Mesh2D> || std::same_as<M, MultiMesh2D>))
		|| (std::same_as<T, Transform3D> && (std::same_as<M, Mesh3D> || std::same_as<M, MultiMesh3D>));

	template<typename T, typename M>
	requires CompatibleObject<T, M>
	struct Object
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

		Object(const T& transform) : m_transform(transform), m_baseMesh(M()), m_mesh(M()) {}
		Object(const T& transform, const M& mesh) : m_transform(transform), m_baseMesh(mesh), m_mesh(mesh) { UPDATE_MESH(); }

		virtual void Update(float dt) { IncrementTransformPos(m_vel * dt); }
		virtual void Draw(Renderer& r, const Camera3D& c = Camera3D()) const = 0;

		inline T GetTransform() const { return m_transform; }
		void SetTransform(const T& transform)
		{
			m_transform = transform;
			m_mesh = m_baseMesh;
			UPDATE_MESH();
		}

		void SetTransformPos(const decltype(std::declval<T>().m_pos)& pos)
		{
			m_transform.m_pos = pos;
			m_mesh = m_baseMesh;
			UPDATE_MESH();
		}
		void IncrementTransformPos(const decltype(std::declval<T>().m_pos)& pos)
		{
			m_transform.m_pos += pos;
			m_mesh = m_baseMesh;
			UPDATE_MESH();
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

	struct Rect2D : Object<Transform2D, Mesh2D>
	{
		Color m_color;

		Rect2D(const Transform2D& t = Transform2D(), const Color& c = Color(1.0f, 1.0f, 1.0f)) :
			Object(t, Rect2DMesh), m_color(c) {}

		void Draw(Renderer& r, const Camera3D& c) const override
		{
			r.SetColor(m_mesh.m_color);
			r.RenderCustomOutline(m_mesh.m_points);
		}
	};

	struct Rect3D : Object<Transform3D, Mesh3D>
	{
		Color m_color;

		Rect3D(const Transform3D& t, const Color& c = Color(1.0f, 1.0f, 1.0f)) :
			Object(t, Rect3DMesh), m_color(c) {}

		void Draw(Renderer& r, const Camera3D& c) const override
		{
			r.SetColor(m_color);
			r.Render3DOutlineTriangles(c, {
				Triangle3D(m_mesh[2], m_mesh[0], m_mesh[1]),
				Triangle3D(m_mesh[1], m_mesh[3], m_mesh[2]),
				Triangle3D(m_mesh[6], m_mesh[2], m_mesh[3]),
				Triangle3D(m_mesh[3], m_mesh[7], m_mesh[6]),
				Triangle3D(m_mesh[4], m_mesh[6], m_mesh[7]),
				Triangle3D(m_mesh[7], m_mesh[5], m_mesh[4]),
				Triangle3D(m_mesh[0], m_mesh[4], m_mesh[5]),
				Triangle3D(m_mesh[5], m_mesh[1], m_mesh[0]),
				Triangle3D(m_mesh[4], m_mesh[0], m_mesh[2]),
				Triangle3D(m_mesh[2], m_mesh[6], m_mesh[4]),
				Triangle3D(m_mesh[5], m_mesh[7], m_mesh[3]),
				Triangle3D(m_mesh[3], m_mesh[1], m_mesh[5])
			});
		}
	};
}