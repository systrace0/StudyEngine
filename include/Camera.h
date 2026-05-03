#pragma once

#include "CameraInput.h"

#include <glm/glm.hpp>

namespace trace
{
	class Camera
	{
	public:
		Camera(F32 aspectRatio, F32 fov = 45.0f, F32 near = 0.1f, F32 far = 100.0f);

		void update(const CameraInput& input, F32 deltaTime);

		void onMouseMove(F32 xPos, F32 yPos);
		void onScroll(F32 yOffset);
		void setAspectRatio(F32 ratio) { m_aspectRatio = ratio; }


		[[nodiscard]] glm::mat4 getViewMatrix()		  const;
		[[nodiscard]] glm::mat4 getProjectionMatrix() const;

		[[nodiscard]] glm::vec3 position() const { return m_position; }
		[[nodiscard]] glm::vec3 forward()  const { return m_forward; }
		void resetFirstMouse() { m_firstMouse = true; }

	private:
		// Position and orientation
		glm::vec3 m_position{ 0.0f, 0.0f, 3.0f };  // start 3 units back from origin
		glm::vec3 m_forward{ 0.0f, 0.0f, -1.0f }; // looking into screen
		glm::vec3 m_right{ 1.0f, 0.0f, 0.0f };
		glm::vec3 m_up{ 0.0f, 1.0f, 0.0f };

		// Euler angles
		F32 m_yaw{ -90.0f }; // -90 so forward points down -Z initially
		F32 m_pitch{ 0.0f };

		// Camera settings
		F32 m_fov{ 45.0f };
		F32 m_aspectRatio{ 0.0f };
		F32 m_near{ 0.1f };
		F32 m_far{ 100.0f };
		F32 m_movementSpeed{ 5.0f };
		F32 m_mouseSensitivity{ 0.1f };

		// Mouse state
		F32 m_lastMouseX{ 0.0f };
		F32 m_lastMouseY{ 0.0f };
		bool m_firstMouse{ true };

		void updateVectors();
	};
}