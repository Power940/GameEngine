#pragma once
#include "Structs.h"
#include <vector>

namespace STR_FALL
{
	struct Mesh2D
	{
		std::vector<Vector2> m_points;
		std::vector<int> m_indices;
		Color m_color;

		inline Mesh2D(const std::vector<Vector2>& points = {}, const Color& color = Color(), const std::vector<int>& indices = {}):
			m_points(points), m_color(color), m_indices(indices) {}

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
	};

	struct MultiMesh2D
	{
		std::vector<Mesh2D> m_meshes;

		inline MultiMesh2D(const std::vector<Mesh2D>& meshes = {}) : m_meshes(meshes) {}

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

		inline Mesh3D(const std::vector<Vector3>& points = {}, const Color& color = Color(), const std::vector<int>& indices = {}):
			m_points(points), m_color(color), m_indices(indices) {}

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
	};

	struct MultiMesh3D
	{
		std::vector<Mesh3D> m_meshes;

		inline MultiMesh3D(const std::vector<Mesh3D>& meshes = {}) : m_meshes(meshes) {}

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
	};

	static Mesh2D Rect2DMesh = Mesh2D(
		{ Vector2(0.5f, -0.5f), Vector2(0.5f, 0.5f), Vector2(-0.5f, 0.5f), Vector2(-0.5f, -0.5f) },
		Color(),
		{ 0,1,2,
		2,4,0 }
	);
	static Mesh3D Rect3DMesh = Mesh3D(
		{ Vector3(0.5f, 0.5f, 0.5f),
		Vector3(0.5f, 0.5f, -0.5f),
		Vector3(0.5f, -0.5f, 0.5f),
		Vector3(0.5f, -0.5f, -0.5f),
		Vector3(-0.5f, 0.5f, 0.5f),
		Vector3(-0.5f, 0.5f, -0.5f),
		Vector3(-0.5f, -0.5f, 0.5f),
		Vector3(-0.5f, -0.5f, -0.5f) },
		Color(),
		{ 2, 0, 1,
		1, 3, 2,
		6, 2, 3,
		3, 7, 6,
		4, 6, 7,
		7, 5, 4,
		0, 4, 5,
		5, 1, 0,
		4, 0, 2,
		2, 6, 4,
		5, 7, 3,
		3, 1, 5 }
	);
}