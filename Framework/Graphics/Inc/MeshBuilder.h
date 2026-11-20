#pragma once

#include "MeshTypes.h"

namespace FirstEngine::Graphics
{
	class MeshBuilder
	{
	public:
		static MeshPC CreateCubePC(float size, const Color& color);
		static MeshPC CreateCubePC(float size);

		static MeshPC CreateRectanglePC(float width, float height,float depth);

		static MeshPC CreatePlanePC(int numRows, int numColumns, float spacing, bool horizontal = true);

		static MeshPC CreateCylinderPC(int slices, int rings);

		static MeshPC CreateSpherePC(int slices, int rings, float radius);

		static MeshPC CreatePyramid(float size);
	private:

	};
}
