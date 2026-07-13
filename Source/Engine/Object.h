#pragma once
#include <cmath>
#include <concepts>
#include <vector>
#include "Structs.h"
#include "Constants.h"
#include "Renderer.h"

namespace STR_FALL
{
	template<typename T>
	concept Transforms = std::same_as<T, Transform2D> || std::same_as<T, Transform3D>;
	template<Transforms T>
	struct Object
	{
	protected:
		T m_transform;

	public:
		Vector3 m_vel = Vector3();

		Object(const T& transform) : m_transform(transform) {}

		virtual void Update(float dt) { m_transform.m_pos += m_vel * dt; }
		virtual void Draw(const Renderer& r) const = 0;
	};

	struct Rect2D : Object<Transform2D>
	{
	protected:
		float halfX; float halfY;

	public:
		Color m_color;

		Rect2D(const Transform2D& t = Transform2D(), const Color& c = Color(1.0f, 1.0f, 1.0f)) :
			Object(t), m_color(c) {
			UpdateHalfExtends();
		}

		inline float Deg() const { return fmod(m_transform.m_rot * F_RAD_DEG, 360.0f); }
		inline float Rad() const { return fmod(m_transform.m_rot, F_PI2); }
		inline void Deg(float val) { m_transform.SetRotation(fmod(val * F_DEG_RAD, F_PI2)); }
		inline void Rad(float val) { m_transform.SetRotation(fmod(val, F_PI2)); }

		inline float MinX() const { return m_transform.m_pos.m_x - halfX; }
		inline float MaxX() const { return m_transform.m_pos.m_x + halfX; }
		inline float MinY() const { return m_transform.m_pos.m_y - halfY; }
		inline float MaxY() const { return m_transform.m_pos.m_y + halfY; }

		void UpdateHalfExtends() {
			Vector2 halfs = m_transform.GetRotationMatrix().Abs() * (m_transform.m_scale * 0.5f);

			halfX = halfs.m_x;
			halfY = halfs.m_y;
		}

		void Draw(const Renderer& r) const override
		{
			r.RenderFillRectAABBColor(*this);
		}
	};

	struct Rect3D : Object<Transform3D>
	{
	protected:
		float m_halfX; float m_halfY; float m_halfZ;
		std::vector<Triangle3D> m_Tris;

	public:
		Color m_color;

		Rect3D(const Transform3D& t, const Color& c = Color(1.0f, 1.0f, 1.0f)) :
			Object(t), m_color(c) {
			UpdateHalfExtends(); UpdateTriangles();
		}


		float DegX() const { return fmod(m_transform.m_rot.m_x * F_RAD_DEG, 360.0f); }
		float DegY() const { return fmod(m_transform.m_rot.m_y * F_RAD_DEG, 360.0f); }
		float DegZ() const { return fmod(m_transform.m_rot.m_z * F_RAD_DEG, 360.0f); }
		float RadX() const { return fmod(m_transform.m_rot.m_x, F_PI2); }
		float RadY() const { return fmod(m_transform.m_rot.m_y, F_PI2); }
		float RadZ() const { return fmod(m_transform.m_rot.m_z, F_PI2); }
		void DegX(float val) { m_transform.SetRotationX(fmod(val * F_DEG_RAD, F_PI2)); }
		void DegY(float val) { m_transform.SetRotationY(fmod(val * F_DEG_RAD, F_PI2)); }
		void DegZ(float val) { m_transform.SetRotationZ(fmod(val * F_DEG_RAD, F_PI2)); }
		void RadX(float val) { m_transform.SetRotationX(fmod(val, F_PI2)); }
		void RadY(float val) { m_transform.SetRotationY(fmod(val, F_PI2)); }
		void RadZ(float val) { m_transform.SetRotationZ(fmod(val, F_PI2)); }

		inline float MinX() const { return m_transform.m_pos.m_x - m_halfX; }
		inline float MaxX() const { return m_transform.m_pos.m_x + m_halfX; }
		inline float MinY() const { return m_transform.m_pos.m_y - m_halfY; }
		inline float MaxY() const { return m_transform.m_pos.m_y + m_halfY; }
		inline float MinZ() const { return m_transform.m_pos.m_z - m_halfZ; }
		inline float MaxZ() const { return m_transform.m_pos.m_z + m_halfZ; }

		void UpdateHalfExtends() {
			Vector3 halfs = m_transform.GetRotationMatrix().Abs() * (m_transform.m_scale * 0.5f);

			m_halfX = halfs.m_x;
			m_halfY = halfs.m_y;
			m_halfZ = halfs.m_z;
		}
		void UpdateTriangles()
		{
			Vector3 hs = m_transform.m_scale * 0.5f;

			std::vector<Vector3> p = {
				m_transform.GetRotationMatrix() * Vector3(m_transform.m_pos.m_x + hs.m_x, m_transform.m_pos.m_y + hs.m_y, m_transform.m_pos.m_z + hs.m_z),
				m_transform.GetRotationMatrix() * Vector3(m_transform.m_pos.m_x + hs.m_x, m_transform.m_pos.m_y + hs.m_y, m_transform.m_pos.m_z - hs.m_z),
				m_transform.GetRotationMatrix() * Vector3(m_transform.m_pos.m_x + hs.m_x, m_transform.m_pos.m_y - hs.m_y, m_transform.m_pos.m_z + hs.m_z),
				m_transform.GetRotationMatrix() * Vector3(m_transform.m_pos.m_x + hs.m_x, m_transform.m_pos.m_y - hs.m_y, m_transform.m_pos.m_z - hs.m_z),
				m_transform.GetRotationMatrix() * Vector3(m_transform.m_pos.m_x - hs.m_x, m_transform.m_pos.m_y + hs.m_y, m_transform.m_pos.m_z + hs.m_z),
				m_transform.GetRotationMatrix() * Vector3(m_transform.m_pos.m_x - hs.m_x, m_transform.m_pos.m_y + hs.m_y, m_transform.m_pos.m_z - hs.m_z),
				m_transform.GetRotationMatrix() * Vector3(m_transform.m_pos.m_x - hs.m_x, m_transform.m_pos.m_y - hs.m_y, m_transform.m_pos.m_z + hs.m_z),
				m_transform.GetRotationMatrix() * Vector3(m_transform.m_pos.m_x - hs.m_x, m_transform.m_pos.m_y - hs.m_y, m_transform.m_pos.m_z - hs.m_z)
			};
			m_Tris = {
				Triangle3D(p[2], p[0], p[1]),
				Triangle3D(p[1], p[3], p[2]),
				Triangle3D(p[6], p[2], p[3]),
				Triangle3D(p[3], p[7], p[6]),
				Triangle3D(p[4], p[6], p[7]),
				Triangle3D(p[7], p[5], p[4]),
				Triangle3D(p[0], p[4], p[5]),
				Triangle3D(p[5], p[1], p[0]),
				Triangle3D(p[4], p[0], p[2]),
				Triangle3D(p[2], p[6], p[4]),
				Triangle3D(p[5], p[7], p[3]),
				Triangle3D(p[3], p[1], p[5])
			};
		}
		std::vector<Triangle3D> GetTris() const
		{
			return m_Tris;
		}

		void Draw(const Renderer& r) const override
		{
		}
	};
}