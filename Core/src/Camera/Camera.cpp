#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace trace
{
	Camera::Camera(F32 aspectRatio, F32 fov, F32 nearPane, F32 farPane)
		: m_aspectRatio(aspectRatio)
		, m_fov(fov)
		, m_near(nearPane)
		, m_far(farPane)
	{
		updateVectors();
	}

	void Camera::update(const CameraInput& input, F32 deltaTime)
	{
		F32 velocity = m_movementSpeed * deltaTime;

		if (input.moveForward) m_position += m_forward * velocity;
		if (input.moveBack)	   m_position -= m_forward * velocity;
		if (input.moveRight)   m_position += m_right * velocity;
		if (input.moveLeft)    m_position -= m_right * velocity;
		if (input.moveUp)	   m_position += glm::vec3(0.0f, 1.0f, 0.0f) * velocity;
		if (input.moveDown)    m_position -= glm::vec3(0.0f, 1.0f, 0.0f) * velocity;
	}

	void Camera::onMouseMove(F32 xPos, F32 yPos)
	{
		if (m_firstMouse)
		{
			m_lastMouseX = xPos;
			m_lastMouseY = yPos;
			m_firstMouse = false;
			return;
		}

		F32 xOffset = (xPos - m_lastMouseX) * m_mouseSensitivity;
		F32 yOffset = (m_lastMouseY - yPos) * m_mouseSensitivity; // reversed - y goes bottom to up

		m_lastMouseX = xPos;
		m_lastMouseY = yPos;

		m_yaw += xOffset;
		m_pitch += yOffset;

		// Prevents gimbal lock
		if (m_pitch > 89.0f) m_pitch = 89.0f;
		if (m_pitch < -89.0f) m_pitch = -89.0f;

		updateVectors();
	}

	void Camera::onScroll(F32 yOffset)
	{
		m_fov -= yOffset;
		if (m_fov < 1.0f)  m_fov = 1.0f;
		if (m_fov > 90.0f) m_fov = 90.0f;
	}

	glm::mat4 Camera::getViewMatrix() const
	{
		return glm::lookAt(m_position, m_position + m_forward, m_up);
	}

	glm::mat4 Camera::getProjectionMatrix() const
	{
		return glm::perspective(glm::radians(m_fov), m_aspectRatio, m_near, m_far);
	}

	void Camera::updateVectors()
	{
		// Compute forward vector from yaw and pitch
		glm::vec3 forward;
		forward.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
		forward.y = sin(glm::radians(m_pitch));
		forward.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
		m_forward = glm::normalize(forward);

		// Derive right and up from forward
		m_right = glm::normalize(glm::cross(m_forward, glm::vec3(0.0f, 1.0f, 0.0f)));
		m_up = glm::normalize(glm::cross(m_right, m_forward));
	}
}