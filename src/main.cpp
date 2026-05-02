#include <cstddef>

#include "Window.h"
#include "Core.h"
#include "Logger.h"

#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "Primitives.h"

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

	glEnable(GL_DEPTH_TEST);

	Logger::info("Engine initialized successfully.");

	ImGuiManager gui{ window };
	gui.registerDefaultPanels();

	Shader shader("shaders/basic.vert", "shaders/basic.frag");
	Mesh quad = trace::Primitives::createQuad();
	Texture texture1("assets/textures/container.jpg");

	shader.use();
	shader.setInt("u_texture", 0);

	while (!window.shouldClose())
	{
		glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 transform = glm::mat4(1.0f);
		transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
		transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

		shader.use();
		shader.setMat4("transform", glm::value_ptr(transform));
		texture1.bind(0);
		quad.draw();

		gui.beginFrame();
		// Panels
		gui.endFrame();

		window.swapBuffers();
		window.pollEvents();
	}

	return 0;
}