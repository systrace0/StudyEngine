#pragma once

#include "Core/Defines.h"

// TODO: Add texCoords[2] to Vertex Struct and static_assert offsetof for texCoord when implementing Textures

namespace trace
{
	struct Vertex
	{
		// TODO: When adding glm -> use glm::vec3 instead of arrays
		F32 position[3];
		F32 color[3];
		F32 texCoords[2];
	};

	// Fires at compile time if accidentally adding a member or change of order causing padding.
	static_assert(sizeof(Vertex) == 32, "Vertex layout has unexpected padding");
	static_assert(offsetof(Vertex, color) == 12, "Vertex color offset wrong - layout changed");
	static_assert(offsetof(Vertex, texCoords) == 24, "Vertex texture offset wrong - layout changed");
}