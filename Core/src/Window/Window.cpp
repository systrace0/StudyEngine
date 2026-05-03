#include "Window.h"

#include <cstdio>
#include <stdexcept>

#include "Core/Defines.h"
#include "Core/Logger.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace trace
{
	Window::Window(int width, int height, const char* title) : m_width(width), m_height(height)
	{
		// Each failure path cleans up what it already initialized
		// This is the alternative to a giant nested if-chain
		if (!glfwInit())
			throw std::runtime_error("Failed to initialize GLFW");

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		// Debug context in debug builds - gives better GL error messages
#ifndef NDEBUG
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif

		m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);

		if (!m_window)
		{
			glfwTerminate();
			throw std::runtime_error("Failed to create GLFW window");
		}

		glfwMakeContextCurrent(m_window);
		glfwSwapInterval(1);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			glfwDestroyWindow(m_window);
			glfwTerminate();
			// throw std::runtime_error("Failed to initialize GLAD");
			Logger::fatal("Failed to initialize GLAD");
		}

		glViewport(0, 0, width, height);

		glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* w, int width, int height)
			{
				glViewport(0, 0, width, height);
			});

		// Setup GL debug output in debug builds after GL context is initialized
#ifndef NDEBUG
		// Enable debug output if available
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback([](GLenum source [[maybe_unused]],
			GLenum type [[maybe_unused]],
			GLuint id [[maybe_unused]],
			GLenum severity,
			GLsizei length [[maybe_unused]],
			const GLchar* message, const void*)
			{
				if (severity == GL_DEBUG_SEVERITY_NOTIFICATION) return;

				if (severity == GL_DEBUG_SEVERITY_HIGH)
					Logger::error("[GL Debug] {}", message);
				else
					Logger::warn("[GL Debug] {}", message);
			}, nullptr);
#endif

		Logger::info("[Window] Created {}x{} | OpenGl {}", width, height, (const char*)glGetString(GL_VERSION));
	}

	Window::~Window()
	{
		// Guard against destroying a moved-from object
		if (m_window)
		{
			glfwDestroyWindow(m_window);
			glfwTerminate();
		}
	}

	Window::Window(Window&& other) noexcept
		: m_window(other.m_window), m_width(other.m_width), m_height(other.m_height)
	{
		// Null out the source so its destructor doesn't double-free
		other.m_window = nullptr;
	}

	Window& Window::operator=(Window&& other) noexcept
	{
		if (this != &other)
		{
			// Release what we currently own
			if (m_window)
			{
				glfwDestroyWindow(m_window);
				glfwTerminate();
			}

			m_window = other.m_window;
			m_width = other.m_width;
			m_height = other.m_height;
			other.m_window = nullptr;
		}
		return *this;
	}

	bool Window::shouldClose() const
	{
		ASSERT(m_window, "Window handle is null in shouldClose()");
		return glfwWindowShouldClose(m_window);
	}

	void Window::swapBuffers() const
	{
		ASSERT(m_window, "Window handle is null in swapBuffers()");
		glfwSwapBuffers(m_window);
	}

	void Window::pollEvents() const
	{
		ASSERT(m_window, "Window handle is null in pollEvents()");
		glfwPollEvents();
	}
} // namespace trace