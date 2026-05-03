#include "App.h"

#include <glm/gtc/type_ptr.hpp>
#include <imgui_impl_glfw.h>

namespace trace
{
	App::App(const AppConfig& config)
		: m_window(config.window.width, config.window.height, config.window.title)
		, m_camera((F32)config.window.width / (F32)config.window.height)
		, m_gui(m_window)
		, m_shader(config.vertexShader, config.fragmentShader)
		, m_texture(config.texture)
		, m_cube(Primitives::createCube())
	{
		setupCallbacks();
		glfwSetInputMode(m_window.handle(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glEnable(GL_DEPTH_TEST);

		m_gui.registerDefaultPanels();

		m_shader.use();
		m_shader.setInt("u_texture", 0);

		Logger::info("[App] Initialized");
	}

	void App::setupCallbacks()
	{
		glfwSetWindowUserPointer(m_window.handle(), &m_camera);

		glfwSetCursorPosCallback(m_window.handle(),
			[](GLFWwindow* w, double x, double y)
			{
				// Chain to ImGui first
				ImGui_ImplGlfw_CursorPosCallback(w, x, y);

				auto* cam = static_cast<Camera*>(glfwGetWindowUserPointer(w));
				if (glfwGetInputMode(w, GLFW_CURSOR) == GLFW_CURSOR_DISABLED)
					cam->onMouseMove((F32)x, (F32)y);
			});

		glfwSetScrollCallback(m_window.handle(),
			[](GLFWwindow* w, double x, double y)
			{
				// Chain to ImGui first
				ImGui_ImplGlfw_ScrollCallback(w, x, y);

				auto* cam = static_cast<Camera*>(glfwGetWindowUserPointer(w));
				if (glfwGetInputMode(w, GLFW_CURSOR) == GLFW_CURSOR_DISABLED)
					cam->onScroll((F32)y);
			});

		glfwSetFramebufferSizeCallback(m_window.handle(),
			[](GLFWwindow*, int w, int h)
			{
				glViewport(0, 0, w, h);
			});
	}

	void App::run()
	{
		while (m_running)
		{
			F32 currentTime = GetTime();
			F32 deltaTime = currentTime - m_lastFrame;
			m_lastFrame = currentTime;

			glfwPollEvents();

			if (m_window.shouldClose())
			{
				stop();
				break;
			}

			pollInput();
			update(deltaTime);
			render();
		}
	}

	void App::stop()
	{
		m_running = false;
	}

	void App::update(F32 deltaTime)
	{
		m_camera.update(m_cameraInput, deltaTime);
	}
	void App::render()
	{
		glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Logger::debug("WantCaptureMouse: {}", ImGui::GetIO().WantCaptureMouse);

		m_camera.setAspectRatio((F32)m_window.width() / (F32)m_window.height());

		m_shader.use();
		m_shader.setMat4("view", glm::value_ptr(m_camera.getViewMatrix()));
		m_shader.setMat4("projection", glm::value_ptr(m_camera.getProjectionMatrix()));

		glm::mat4 model = glm::mat4(1.0f);
		m_shader.setMat4("model", glm::value_ptr(model));

		m_texture.bind(0);
		m_cube.draw();

		m_gui.beginFrame();
		m_gui.endFrame();

		m_window.swapBuffers();
	}

	void App::pollInput()
	{
		static bool escPressed = false;
		bool escDown = glfwGetKey(m_window.handle(), GLFW_KEY_ESCAPE) == GLFW_PRESS;
		if (escDown && !escPressed)
		{
			m_mouseCaptured = !m_mouseCaptured;
			glfwSetInputMode(m_window.handle(), GLFW_CURSOR,
				m_mouseCaptured ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
			m_camera.resetFirstMouse();
		}
		escPressed = escDown;
		m_cameraInput.moveForward = m_mouseCaptured && glfwGetKey(m_window.handle(), GLFW_KEY_W) == GLFW_PRESS;
		m_cameraInput.moveBack = m_mouseCaptured && glfwGetKey(m_window.handle(), GLFW_KEY_S) == GLFW_PRESS;
		m_cameraInput.moveLeft = m_mouseCaptured && glfwGetKey(m_window.handle(), GLFW_KEY_A) == GLFW_PRESS;
		m_cameraInput.moveRight = m_mouseCaptured && glfwGetKey(m_window.handle(), GLFW_KEY_D) == GLFW_PRESS;
		m_cameraInput.moveUp = m_mouseCaptured && glfwGetKey(m_window.handle(), GLFW_KEY_SPACE) == GLFW_PRESS;
		m_cameraInput.moveDown = m_mouseCaptured && glfwGetKey(m_window.handle(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS;
	}

	F32 App::GetTime()
	{
		return (F32)glfwGetTime();
	}
}