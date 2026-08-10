#pragma once
#include "Structs.h"
#include "Texture.h"
#include <vector>
#include <array>

namespace STR_FALL
{
	struct Mesh2D;
	struct MultiMesh2D;
	struct Mesh3d;
	struct MultiMesh3D;

	struct Mesh2D
	{
		std::vector<Vector2> m_points;
		std::vector<int> m_indices;
		Color m_color;

		inline Mesh2D(const std::vector<Vector2>& points = {}, const Color& color = Color(), const std::vector<int>& indices = {}):
			m_points(points), m_color(color), m_indices(indices) {}
		inline Mesh2D(const MultiMesh2D& meshs);

		Mesh2D operator+(const Vector2& rhs) const
		{
			std::vector<Vector2> newPoints;
			for (const Vector2& point : m_points) { newPoints.push_back(point + rhs); }
			return Mesh2D(newPoints, m_color);
		}
		Mesh2D operator-(const Vector2& rhs) const
		{
			std::vector<Vector2> newPoints;
			for (const Vector2& point : m_points) { newPoints.push_back(point - rhs); }
			return Mesh2D(newPoints, m_color);
		}
		Mesh2D operator*(const Vector2& rhs) const
		{
			std::vector<Vector2> newPoints;
			for (const Vector2& point : m_points) { newPoints.push_back(point * rhs); }
			return Mesh2D(newPoints, m_color);
		}
		Mesh2D operator/(const Vector2& rhs) const
		{
			std::vector<Vector2> newPoints;
			for (const Vector2& point : m_points) { newPoints.push_back(point / rhs); }
			return Mesh2D(newPoints, m_color);
		}
		Mesh2D operator+=(const Vector2& rhs)
		{
			for (Vector2& point : m_points) { point += rhs; }
			return *this;
		}
		Mesh2D operator-=(const Vector2& rhs)
		{
			for (Vector2& point : m_points) { point -= rhs; }
			return *this;
		}
		Mesh2D operator*=(const Vector2& rhs)
		{
			for (Vector2& point : m_points) { point *= rhs; }
			return *this;
		}
		Mesh2D operator/=(const Vector2& rhs)
		{
			for (Vector2& point : m_points) { point /= rhs; }
			return *this;
		}

		Mesh2D operator*(const Matrix2& rhs) const
		{
			std::vector<Vector2> newPoints;
			for (const Vector2& point : m_points) { newPoints.push_back(point * rhs); }
			return Mesh2D(newPoints, m_color);
		}
		Mesh2D operator*=(const Matrix2& rhs)
		{
			for (Vector2& point : m_points) { point *= rhs; }
			return *this;
		}

		Vector2 operator[](const unsigned int element) const { assert(element < m_points.size()); return m_points[element]; }
		Vector2& operator[](const unsigned int element) { assert(element < m_points.size()); return m_points[element]; }

		std::array<float, 2> GetFurthestPoints()
		{
			float x = 0.0f, y = 0.0f;
			for (Vector2 vec : m_points)
			{
				if (abs(vec.m_x) > abs(x))
				{
					x = vec.m_x;
				}
				if (abs(vec.m_y) > abs(y))
				{
					y = vec.m_y;
				}
			}
			return { x, y };
		}
	};

	struct MultiMesh2D
	{
		std::vector<Mesh2D> m_meshes;

		inline MultiMesh2D(const std::vector<Mesh2D>& meshes = {}) : m_meshes(meshes) {}
		inline MultiMesh2D(const Mesh2D& mesh) : m_meshes({ mesh }) {}

		MultiMesh2D operator+(const Vector2& rhs) const
		{
			std::vector<Mesh2D> newMeshes;
			std::vector<Vector2> newPoints;
			for (const Mesh2D& mesh : m_meshes)
			{
				for (const Vector2& point : mesh.m_points) { newPoints.push_back(point + rhs); }
				newMeshes.push_back(Mesh2D(newPoints, mesh.m_color));
				newPoints.clear();
			}
			return MultiMesh2D(newMeshes);
		}
		MultiMesh2D operator-(const Vector2& rhs) const
		{
			std::vector<Mesh2D> newMeshes;
			std::vector<Vector2> newPoints;
			for (const Mesh2D& mesh : m_meshes)
			{
				for (const Vector2& point : mesh.m_points) { newPoints.push_back(point - rhs); }
				newMeshes.push_back(Mesh2D(newPoints, mesh.m_color));
				newPoints.clear();
			}
			return MultiMesh2D(newMeshes);
		}
		MultiMesh2D operator*(const Vector2& rhs) const
		{
			std::vector<Mesh2D> newMeshes;
			std::vector<Vector2> newPoints;
			for (const Mesh2D& mesh : m_meshes)
			{
				for (const Vector2& point : mesh.m_points) { newPoints.push_back(point * rhs); }
				newMeshes.push_back(Mesh2D(newPoints, mesh.m_color));
				newPoints.clear();
			}
			return MultiMesh2D(newMeshes);
		}
		MultiMesh2D operator/(const Vector2& rhs) const
		{
			std::vector<Mesh2D> newMeshes;
			std::vector<Vector2> newPoints;
			for (const Mesh2D& mesh : m_meshes)
			{
				for (const Vector2& point : mesh.m_points) { newPoints.push_back(point / rhs); }
				newMeshes.push_back(Mesh2D(newPoints, mesh.m_color));
				newPoints.clear();
			}
			return MultiMesh2D(newMeshes);
		}
		MultiMesh2D operator+=(const Vector2& rhs)
		{
			for (Mesh2D& mesh : m_meshes) { for (Vector2& point : mesh.m_points) { point += rhs; } }
			return *this;
		}
		MultiMesh2D operator-=(const Vector2& rhs)
		{
			for (Mesh2D& mesh : m_meshes) { for (Vector2& point : mesh.m_points) { point -= rhs; } }
			return *this;
		}
		MultiMesh2D operator*=(const Vector2& rhs)
		{
			for (Mesh2D& mesh : m_meshes) { for (Vector2& point : mesh.m_points) { point *= rhs; } }
			return *this;
		}
		MultiMesh2D operator/=(const Vector2& rhs)
		{
			for (Mesh2D& mesh : m_meshes) { for (Vector2& point : mesh.m_points) { point /= rhs; } }
			return *this;
		}

		MultiMesh2D operator*(const Matrix2& rhs) const
		{
			std::vector<Mesh2D> newMeshes;
			std::vector<Vector2> newPoints;
			for (const Mesh2D& mesh : m_meshes)
			{
				for (const Vector2& point : mesh.m_points) { newPoints.push_back(point * rhs); }
				newMeshes.push_back(Mesh2D(newPoints, mesh.m_color));
				newPoints.clear();
			}
			return MultiMesh2D(newMeshes);
		}
		MultiMesh2D operator*=(const Matrix2& rhs)
		{
			for (Mesh2D& mesh : m_meshes) { for (Vector2& point : mesh.m_points) { point *= rhs; } }
			return *this;
		}

		Mesh2D operator[](const unsigned int element) const { assert(element < m_meshes.size()); return m_meshes[element]; }
		Mesh2D& operator[](const unsigned int element) { assert(element < m_meshes.size()); return m_meshes[element]; }
	};

	struct Mesh3D
	{
		std::vector<Vector3> m_points;
		std::vector<int> m_indices;
		Color m_color;
		std::vector<Vector2> m_pointsUV;
		res_t<Texture> m_texture;

		inline Mesh3D(const std::vector<Vector3>& points = {}, const Color& color = Color(), const std::vector<int>& indices = {}, const std::vector<Vector2>& pointsUV = {}, const res_t<Texture>& texture = nullptr) :
			m_points(points), m_color(color), m_indices(indices), m_pointsUV(pointsUV), m_texture(texture) {}
		inline Mesh3D(const MultiMesh3D& meshs);

		Mesh3D operator+(const Vector3& rhs) const
		{
			std::vector<Vector3> newPoints;
			for (const Vector3& point : m_points) { newPoints.push_back(point + rhs); }
			return Mesh3D(newPoints, m_color);
		}
		Mesh3D operator-(const Vector3& rhs) const
		{
			std::vector<Vector3> newPoints;
			for (const Vector3& point : m_points) { newPoints.push_back(point - rhs); }
			return Mesh3D(newPoints, m_color);
		}
		Mesh3D operator*(const Vector3& rhs) const
		{
			std::vector<Vector3> newPoints;
			for (const Vector3& point : m_points) { newPoints.push_back(point * rhs); }
			return Mesh3D(newPoints, m_color);
		}
		Mesh3D operator/(const Vector3& rhs) const
		{
			std::vector<Vector3> newPoints;
			for (const Vector3& point : m_points) { newPoints.push_back(point / rhs); }
			return Mesh3D(newPoints, m_color);
		}
		Mesh3D operator+=(const Vector3& rhs)
		{
			for (Vector3& point : m_points) { point += rhs; }
			return *this;
		}
		Mesh3D operator-=(const Vector3& rhs)
		{
			for (Vector3& point : m_points) { point -= rhs; }
			return *this;
		}
		Mesh3D operator*=(const Vector3& rhs)
		{
			for (Vector3& point : m_points) { point *= rhs; }
			return *this;
		}
		Mesh3D operator/=(const Vector3& rhs)
		{
			for (Vector3& point : m_points) { point /= rhs; }
			return *this;
		}

		Mesh3D operator*(const Matrix3& rhs) const
		{
			std::vector<Vector3> newPoints;
			for (const Vector3& point : m_points) { newPoints.push_back(point * rhs); }
			return Mesh3D(newPoints, m_color);
		}
		Mesh3D operator*=(const Matrix3& rhs)
		{
			for (Vector3& point : m_points) { point *= rhs; }
			return *this;
		}

		Vector3 operator[](const unsigned int element) const { assert(element < m_points.size()); return m_points[element]; }
		Vector3& operator[](const unsigned int element) { assert(element < m_points.size()); return m_points[element]; }

		float GetRadius(Vector3 translation = Vector3())
		{
			float dist = -1.0f;
			for (Vector3 vec : m_points)
			{
				vec -= translation;
				dist = (vec.Magnitude() > dist) ? vec.Magnitude() : dist;
			}
			return dist;
		}
	};

	struct MultiMesh3D
	{
		std::vector<Mesh3D> m_meshes;

		inline MultiMesh3D(const std::vector<Mesh3D>& meshes = {}) : m_meshes(meshes) {}
		inline MultiMesh3D(const Mesh3D& mesh) : m_meshes({ mesh }) {}

		MultiMesh3D operator+(const Vector3& rhs) const
		{
			std::vector<Mesh3D> newMeshes;
			std::vector<Vector3> newPoints;
			for (const Mesh3D& mesh : m_meshes)
			{
				for (const Vector3& point : mesh.m_points) { newPoints.push_back(point + rhs); }
				newMeshes.push_back(Mesh3D(newPoints, mesh.m_color));
				newPoints.clear();
			}
			return MultiMesh3D(newMeshes);
		}
		MultiMesh3D operator-(const Vector3& rhs) const
		{
			std::vector<Mesh3D> newMeshes;
			std::vector<Vector3> newPoints;
			for (const Mesh3D& mesh : m_meshes)
			{
				for (const Vector3& point : mesh.m_points) { newPoints.push_back(point - rhs); }
				newMeshes.push_back(Mesh3D(newPoints, mesh.m_color));
				newPoints.clear();
			}
			return MultiMesh3D(newMeshes);
		}
		MultiMesh3D operator*(const Vector3& rhs) const
		{
			std::vector<Mesh3D> newMeshes;
			std::vector<Vector3> newPoints;
			for (const Mesh3D& mesh : m_meshes)
			{
				for (const Vector3& point : mesh.m_points) { newPoints.push_back(point * rhs); }
				newMeshes.push_back(Mesh3D(newPoints, mesh.m_color));
				newPoints.clear();
			}
			return MultiMesh3D(newMeshes);
		}
		MultiMesh3D operator/(const Vector3& rhs) const
		{
			std::vector<Mesh3D> newMeshes;
			std::vector<Vector3> newPoints;
			for (const Mesh3D& mesh : m_meshes)
			{
				for (const Vector3& point : mesh.m_points) { newPoints.push_back(point / rhs); }
				newMeshes.push_back(Mesh3D(newPoints, mesh.m_color));
				newPoints.clear();
			}
			return MultiMesh3D(newMeshes);
		}
		MultiMesh3D operator+=(const Vector3& rhs)
		{
			for (Mesh3D& mesh : m_meshes) { for (Vector3& point : mesh.m_points) { point += rhs; } }
			return *this;
		}
		MultiMesh3D operator-=(const Vector3& rhs)
		{
			for (Mesh3D& mesh : m_meshes) { for (Vector3& point : mesh.m_points) { point -= rhs; } }
			return *this;
		}
		MultiMesh3D operator*=(const Vector3& rhs)
		{
			for (Mesh3D& mesh : m_meshes) { for (Vector3& point : mesh.m_points) { point *= rhs; } }
			return *this;
		}
		MultiMesh3D operator/=(const Vector3& rhs)
		{
			for (Mesh3D& mesh : m_meshes) { for (Vector3& point : mesh.m_points) { point /= rhs; } }
			return *this;
		}

		MultiMesh3D operator*(const Matrix3& rhs) const
		{
			std::vector<Mesh3D> newMeshes;
			std::vector<Vector3> newPoints;
			for (const Mesh3D& mesh : m_meshes)
			{
				for (const Vector3& point : mesh.m_points) { newPoints.push_back(point * rhs); }
				newMeshes.push_back(Mesh3D(newPoints, mesh.m_color));
				newPoints.clear();
			}
			return MultiMesh3D(newMeshes);
		}
		MultiMesh3D operator*=(const Matrix3& rhs)
		{
			for (Mesh3D& mesh : m_meshes) { for (Vector3& point : mesh.m_points) { point *= rhs; } }
			return *this;
		}

		Mesh3D operator[](const unsigned int element) const { assert(element < m_meshes.size()); return m_meshes[element]; }
		Mesh3D& operator[](const unsigned int element) { assert(element < m_meshes.size()); return m_meshes[element]; }

		float GetRadius(Vector3 translation = Vector3(), int meshIndex = 0)
		{
			float dist = -1.0f;
			for (Vector3 vec : m_meshes[0].m_points)
			{
				vec -= translation;
				dist = (vec.Magnitude() > dist) ? vec.Magnitude() : dist;
			}
			return dist;
		}
	};

	inline Mesh2D::Mesh2D(const MultiMesh2D& meshs) : m_points(meshs[0].m_points), m_color(meshs[0].m_color), m_indices(meshs[0].m_indices) {}
	inline Mesh3D::Mesh3D(const MultiMesh3D& meshs) : m_points(meshs[0].m_points), m_color(meshs[0].m_color), m_indices(meshs[0].m_indices) {}
}