#pragma once

#include "Core.h"

namespace trace
{
	struct CameraInput
	{
		bool moveForward{ false };
		bool moveBack{ false };
		bool moveLeft{ false };
		bool moveRight{ false };
		F32 mouseDeltaX{ 0.0f };
		F32 mouseDeltaY{ 0.0f };
		F32 scrollDelta{ 0.0f };
	};
}