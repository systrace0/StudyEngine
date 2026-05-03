#include <cstddef>

#include "Window.h"
#include "Core.h"
#include "Logger.h"

#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "Primitives.h"
#include "Camera.h"

#include "imgui/ImGuiManager.h"
#include "imgui/panels/DebugPanel.h"
#include "imgui/panels/LogPanel.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "glad/glad.h"

using namespace trace;

int main()
{
	Logger::init();

	// Window owns everything
	Window window{ 1280, 720, "TRACE Engine" };

	Camera camera{ (F32)window.width() / (F32)window.height() };

	// Register mouse callback
	glfwSetWindowUserPointer(window.handle(), &camera);
	glfwSetCursorPosCallback(window.handle(), [](GLFWwindow* w, double xPos, double yPos)
		{
			Camera* cam = static_cast<Camera*>(glfwGetWindowUserPointer(w));
			// Only look around when cursor is captured
			if (glfwGetInputMode(w, GLFW_CURSOR) == GLFW_CURSOR_DISABLED)
				cam->onMouseMove((F32)xPos, (F32)yPos);
		});

	// Capute mouse cursor
	glfwSetInputMode(window.handle(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	Logger::info("Engine initialized successfully.");

	ImGuiManager gui{ window };
	gui.registerDefaultPanels();

	Shader shader("shaders/basic.vert", "shaders/basic.frag");
	Texture texture1("assets/textures/container.jpg");
	Mesh cube = trace::Primitives::createCube();

	shader.use();
	shader.setInt("u_texture", 0);

	// Timing
	F32 deltaTime{ 0.0f };
	F32 lastFrame{ 0.0f };

	bool mouseCaptured{ true };

	glEnable(GL_DEPTH_TEST);

	while (!window.shouldClose())
	{
		// Delta time
		F32 currentFrame = (F32)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Poll input
		static bool escPressed = false;
		bool escDown = glfwGetKey(window.handle(), GLFW_KEY_ESCAPE) == GLFW_PRESS;
		if (escDown && !escPressed)
		{
			mouseCaptured = !mouseCaptured;
			glfwSetInputMode(window.handle(), GLFW_CURSOR,
				mouseCaptured ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
			camera.resetFirstMouse();
		}
		escPressed = escDown;

		CameraInput input;
		input.moveForward = mouseCaptured && glfwGetKey(window.handle(), GLFW_KEY_W) == GLFW_PRESS;
		input.moveBack = mouseCaptured && glfwGetKey(window.handle(), GLFW_KEY_S) == GLFW_PRESS;
		input.moveLeft = mouseCaptured && glfwGetKey(window.handle(), GLFW_KEY_A) == GLFW_PRESS;
		input.moveRight = mouseCaptured && glfwGetKey(window.handle(), GLFW_KEY_D) == GLFW_PRESS;
		input.moveUp = mouseCaptured && glfwGetKey(window.handle(), GLFW_KEY_SPACE) == GLFW_PRESS;
		input.moveDown = mouseCaptured && glfwGetKey(window.handle(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS;

		camera.update(input, deltaTime);

		glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.use();
		glm::mat4 model = glm::mat4(1.0f);

		shader.setMat4("model", glm::value_ptr(model));
		shader.setMat4("view", glm::value_ptr(camera.getViewMatrix()));
		shader.setMat4("projection", glm::value_ptr(camera.getProjectionMatrix()));


		texture1.bind(0);
		cube.draw();

		gui.beginFrame();
		// Panels
		gui.endFrame();

		window.swapBuffers();
		window.pollEvents();
	}

	return 0;
}