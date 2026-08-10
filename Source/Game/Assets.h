#pragma once
#include <StarFallEngine.h>

using namespace STR_FALL;


static Mesh3D markerMesh = Mesh3D(
	{
		VertexUV3D(0.0f,0.0f,0.82f,0.0f,0.0f),
		VertexUV3D(0.58f,0.0f,0.0f,0.0f,1.0f),
		VertexUV3D(-0.29f,0.5f,0.0f,1.0f,0.0f),
		VertexUV3D(-0.29f,-0.5f,0.0f,1.0f,1.0f)
	},
	{
		1,2,3,
		0,1,2,
		0,1,3,
		0,2,3
	}
);

static Mesh3D bulletMesh = Mesh3D(
	{ Vector3(0.0f,0.0f,0.25f), Vector3(0.01f,0.0f,-0.25f), Vector3(-0.01f,0.0f,-0.25f) },
	{ 0,1,2 }
);

static MultiMesh3D SpaceShip3D = MultiMesh3D({
	Mesh3D(
		{Vector3(0.0f, 0.0f, 0.5f), Vector3(0.5f, 0.0f, -0.5f), Vector3(-0.5f, 0.0f, -0.5f), Vector3(0.0f, 0.0f, -0.25f), Vector3(0.0f, 0.1f, 0.0f), Vector3(0.0f, -0.1f, 0.0f)},
		{
			0,1,5,
			0,1,4,
			0,2,4,
			0,2,5,
			3,2,5,
			3,2,4,
			3,1,4,
			3,1,5
		}
	),
	Mesh3D(
		{Vector3(0.0f,-0.05f,0.25f), Vector3(0.0f,-0.08f,0.1f), Vector3(0.1f,-0.03f,0.15f), Vector3(-0.1f,-0.03f,0.15f)},
		{
			0,2,1,
			0,3,1
		},
		Color(0.0f, 0.0f, 1.0f)
	),
	Mesh3D(
		{Vector3(0.0f,0.0f,-0.4f), Vector3(0.0f,0.0f,-1.0f), Vector3(0.2f,0.0f,-0.6f), Vector3(-0.2f,0.0f,-0.6f), Vector3(0.0f,-0.2f,-0.6f), Vector3(0.0f,0.2f,-0.6f)},
		{
			0,4,3,
			0,5,3,
			0,2,5,
			0,2,4,
			1,4,3,
			1,5,3,
			1,2,5,
			1,2,4
		},
		Color(1.0f, 1.0f, 0.5f)
	)
	});