#pragma once

// Forward declare to avoid pulling GLFW into every file that include Window.h
// Only Window.cpp needs the full GLFW header
struct GLFWwindow;

namespace trace
{
	class Window
	{
	public:
		// Explicit: prevents accidental implicit conversions
		explicit Window(int width, int height, const char* title);
		~Window();

		// RAII enforcement: one owner, no copies
		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;

		// Move is allowed due transfer of ownership
		Window(Window&& other) noexcept;
		Window& operator=(Window&& other) noexcept;

		// Query - const because they don't modify state
		[[nodiscard]] bool shouldClose() const;
		[[nodiscard]] int width()  const
		{
			int w, h;
			glfwGetWindowSize(m_window, &w, &h);
			return w;
		}

		[[nodiscard]] int height() const
		{
			int w, h;
			glfwGetWindowSize(m_window, &w, &h);
			return h;
		}

		// Actions
		void swapBuffers() const;
		void pollEvents() const;

		// Raw handle - for when other systems (input, imgui) need it
		// Returns pointer, not reference - nullptr is valid "not set" state
		[[nodiscard]] GLFWwindow* handle() const { return m_window; }

	private:
		GLFWwindow* m_window = nullptr;
		int m_width = 0;
		int m_height = 0;
	};
}