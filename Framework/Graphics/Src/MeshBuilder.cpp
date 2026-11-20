#include "Precompiled.h"
#include "MeshBuilder.h"

using namespace FirstEngine;
using namespace FirstEngine::Graphics;

namespace
{
	Color GetNextColor(int& index)
	{
		constexpr Color colorTable[] = {
			Colors::Red,
			Colors::Yellow,
			Colors::Blue,
			Colors::Pink,
			Colors::Purple,
			Colors::Green,
			Colors::Gray,
			Colors::Aqua,
			Colors::Brown,
			Colors::Coral,
			Colors::DarkMagenta
		};

		index = (index + 1) % std::size(colorTable);
		return colorTable[index];
	}

	void CreateCubeIndices(std::vector<uint32_t>& indices)
	{
		indices = {
			// front
			0,1,2,
			0,2,3,
			//back
			7,5,4,
			7,6,5,
			//right
			3,2,6,
			3,6,7,
			//left
			4,5,1,
			4,1,0,
			//top
			1,5,6,
			1,6,2,
			//bottom
			0,3,7,
			0,7,4
		};
	}

	void CreatePlaneIndices(std::vector<uint32_t>& indices, int numRows, int numColums)
	{
		for (int r = 0; r < numRows; ++r)
		{
			for (int c = 0; c < numColums; ++c)
			{
				int i = (r * (numColums + 1)) + c;
				indices.push_back(i);
				indices.push_back(i + numColums + 1);
				indices.push_back(i + numColums + 2);

				indices.push_back(i);
				indices.push_back(i + numColums + 2);
				indices.push_back(i + 1);
			}
		}
	}

	void CreatePyramidIndices(std::vector<uint32_t>& indices)
	{
		indices = {
			// front
			0, 4, 3,
			// right
			3, 4, 2,
			// back
			2, 4, 1,
			// left
			1, 4, 0,
			// bottom
			0, 2, 1,
			0, 3, 2
		};
	}
}

MeshPC MeshBuilder::CreateCubePC(float size, const Color& color)
{
	MeshPC mesh;

	const float hs = size * 0.5f;
	mesh.vertices.push_back({ {-hs,-hs,-hs},color });
	mesh.vertices.push_back({ {-hs, hs,-hs},color });
	mesh.vertices.push_back({ { hs, hs,-hs},color });
	mesh.vertices.push_back({ { hs,-hs,-hs},color });

	mesh.vertices.push_back({ {-hs,-hs, hs},color });
	mesh.vertices.push_back({ {-hs, hs, hs},color });
	mesh.vertices.push_back({ { hs, hs, hs},color });
	mesh.vertices.push_back({ { hs,-hs, hs},color });

	CreateCubeIndices(mesh.indices);
	return mesh;
}

MeshPC MeshBuilder::CreateCubePC(float size)
{
	MeshPC mesh;
	const float hs = size * 0.5f;

	int index = 0;

	mesh.vertices.push_back({ {-hs,-hs,-hs},GetNextColor(index) });
	mesh.vertices.push_back({ {-hs, hs,-hs},GetNextColor(index) });
	mesh.vertices.push_back({ { hs, hs,-hs},GetNextColor(index) });
	mesh.vertices.push_back({ { hs,-hs,-hs},GetNextColor(index) });

	mesh.vertices.push_back({ {-hs,-hs, hs},GetNextColor(index) });
	mesh.vertices.push_back({ {-hs, hs, hs},GetNextColor(index) });
	mesh.vertices.push_back({ { hs, hs, hs},GetNextColor(index) });
	mesh.vertices.push_back({ { hs,-hs, hs},GetNextColor(index) });

	mesh.indices = {
		// front
		0,1,2,
		0,2,3,
		//back
		7,5,4,
		7,6,5,
		//right
		3,2,6,
		3,6,7,
		//left
		4,5,1,
		4,1,0,
		//top
		1,5,6,
		1,6,2,
		//bottom
		0,3,7,
		0,7,4
	};
	return mesh;
}

MeshPC MeshBuilder::CreateRectanglePC(float width, float height, float depth)
{
	MeshPC mesh;

	int index = 0;

	const float hw = width * 0.5f;
	const float hh = height * 0.5f;
	const float hd = depth * 0.5f;

	mesh.vertices.push_back({ {-hw,-hh,-hd},GetNextColor(index) });
	mesh.vertices.push_back({ {-hw, hh,-hd},GetNextColor(index) });
	mesh.vertices.push_back({ { hw, hh,-hd},GetNextColor(index) });
	mesh.vertices.push_back({ { hw,-hh,-hd},GetNextColor(index) });

	mesh.vertices.push_back({ {-hw,-hh, hd},GetNextColor(index) });
	mesh.vertices.push_back({ {-hw, hh, hd},GetNextColor(index) });
	mesh.vertices.push_back({ { hw, hh, hd},GetNextColor(index) });
	mesh.vertices.push_back({ { hw,-hh, hd},GetNextColor(index) });

	CreateCubeIndices(mesh.indices);
	return mesh;
}

MeshPC MeshBuilder::CreatePlanePC(int numRows, int numColumns, float spacing, bool horizontal)
{
	MeshPC mesh;

	int index = 0;

	const float hpw = static_cast<float>(numRows) * spacing * 0.5f;
	const float hph = static_cast<float>(numColumns) * spacing * 0.5f;
	float w = -hpw;
	float h = -hph;
	for (int r = 0; r <= numRows; ++r)
	{
		for (int c = 0; c <= numColumns; ++c)
		{
			Math::Vector3 pos = (horizontal) ? Math::Vector3(w, 0.0f, h) : Math::Vector3(w, h, 0.0f);
			mesh.vertices.push_back({ pos,GetNextColor(index) });
			w += spacing;
		}
		w = -hpw;
		h += spacing;
	}
	CreatePlaneIndices(mesh.indices, numRows, numColumns);

	return mesh;
}

MeshPC MeshBuilder::CreateCylinderPC(int slices, int rings)
{
	MeshPC mesh;

	int index = 0;

	const float hh = static_cast<float>(rings) * 0.5f;
	const float fSlices = static_cast<float>(slices);

	for (int r = 0; r <= rings; ++r)
	{
		float ring = static_cast<float>(r);
		for (int s = 0; s <= slices; ++s)
		{
			float slice = static_cast<float>(s);
			float rotation = (slice / fSlices) * Math::Constants::TwoPi;

			mesh.vertices.push_back({ {
					sin(rotation),
					ring - hh,
					-cos(rotation)},
					GetNextColor(index) });
		}
	}
	CreatePlaneIndices(mesh.indices, rings, slices);

	mesh.vertices.push_back({ {0.0f,hh,0.0f},GetNextColor(index) });
	mesh.vertices.push_back({ {0.0f,-hh,0.0f},GetNextColor(index) });

	int topIndex = mesh.vertices.size() - 2;
	int bottomIndex = mesh.vertices.size() - 1;
	for (int s = 0; s < slices; ++s)
	{
		mesh.indices.push_back(bottomIndex);
		mesh.indices.push_back(s);
		mesh.indices.push_back(s + 1);

		int topRowIndex = topIndex - slices - 1 + s;
		mesh.indices.push_back(topIndex);
		mesh.indices.push_back(topRowIndex + 1);
		mesh.indices.push_back(topRowIndex);
	}


	return mesh;
}

MeshPC MeshBuilder::CreateSpherePC(int slices, int rings, float radius)
{
	MeshPC mesh;

	int index = 0;
	const float vertRotation = (Math::Constants::Pi / static_cast<float>(rings));
	const float horzRotation = (Math::Constants::TwoPi / static_cast<float>(slices));

	for (int r = 0; r <= rings; ++r)
	{
		float ring = static_cast<float>(r);
		float phi = ring * vertRotation;
		for (int s = 0; s <= slices; ++s)
		{
			float slice = static_cast<float>(s);
			float rotation = slice * horzRotation;

			mesh.vertices.push_back({ {
					radius * sin(rotation) * sin(phi),
					radius * cos(phi),
					radius * cos(rotation) * sin(phi)},
					GetNextColor(index) });
		}
	}
	CreatePlaneIndices(mesh.indices,rings, slices);

	return mesh;
}

MeshPC MeshBuilder::CreatePyramid(float size)
{
	MeshPC mesh;

	int index = 0;
	const float hs = size * 0.5f;

	// base corners
	mesh.vertices.push_back({ {-hs, -hs, -hs}, GetNextColor(index) });	// 0 front-left
	mesh.vertices.push_back({ {-hs, -hs,  hs}, GetNextColor(index) });	// 1 back-left
	mesh.vertices.push_back({ { hs, -hs,  hs}, GetNextColor(index) });	// 2 back-right
	mesh.vertices.push_back({ { hs, -hs, -hs}, GetNextColor(index) });	// 3 front-right

	// apex
	mesh.vertices.push_back({ { 0.0f, hs, 0.0f}, GetNextColor(index) });	// 4 apex

	CreatePyramidIndices(mesh.indices);

	return mesh;
}

