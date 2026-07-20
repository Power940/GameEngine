#pragma once
#include <Object.h>
#include <StarFallEngine.h>

using namespace STR_FALL;

static Mesh3D markerMesh = Mesh3D(
	{Vector3(0.0f,0.0f,0.82f), Vector3(0.58f,0.0f,0.0f), Vector3(-0.29f,0.5f,0.0f), Vector3(-0.29f,-0.5f,0.0f)},
	Color(),
	{
		1,2,3,
		0,1,2,
		0,1,3,
		0,2,3
	}
);

struct Marker : public Object<Transform3D, Mesh3D>
{
	Marker(const Transform3D& t) :
		Object(t, markerMesh) {}

	void Update(float dt) override
	{
		return;
	}

	void Draw(Renderer& r, const Camera3D& c = Camera3D::Empty) const override
	{
		r.SetColor(Color());
		g_engine.m_renderer.Render3DCustomOutline(c, m_mesh.m_points, m_mesh.m_indices);
	}
};