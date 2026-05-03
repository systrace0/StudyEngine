#pragma once

#include "AppConfig.h"
#include "Window/Window.h"
#include "Camera/Camera.h"
#include "ImGui/ImGuiManager.h"
#include "Core/Defines.h"
#include "Renderer/Primitives.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"
#include "Renderer/Mesh.h"

namespace trace
{
	class App
	{
	public:
		explicit App(const AppConfig& config);
		~App() = default;

		void run();
		void stop();

	private:
		void update(F32 deltaTime);
		void render();
		void pollInput();
		void setupCallbacks();
		static F32 GetTime();

		Window       m_window;
		Camera       m_camera;
		CameraInput  m_cameraInput;
		ImGuiManager m_gui;
		Shader       m_shader;
		Texture      m_texture;
		Mesh         m_cube;

		bool m_running{ true };
		bool m_mouseCaptured{ true };
		F32 m_lastFrame{ 0.0f };
	};
}