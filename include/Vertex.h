#pragma once

#include "Core.h"

namespace trace
{
	struct Vertex
	{
		// TODO: When adding glm -> use glm::vec3 instead of arrays
		F32 position[3];
		F32 color[3];
		// F32 texCoords[2]; <- Later when applying Textures
	};

	static_assert(sizeof(Vertex) == 24, "Vertex layout has unexpected padding");
}