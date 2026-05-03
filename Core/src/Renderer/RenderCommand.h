#pragma once

#include "Core/Defines.h"

namespace trace
{
	class VertexArray;

	namespace RenderCommand
	{
		static void setClearColor(F32 r, F32 g, F32 b, F32 a);
		static void clear();
		static void drawIndexed(const VertexArray& va);
	}
}