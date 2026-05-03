#include "ImGuiManager.h"

#include "Core/Defines.h"

#include "panels/DebugPanel.h"
#include "panels/LogPanel.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace trace
{
	ImGuiManager::ImGuiManager(Window& window)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

		bool glfwResult = ImGui_ImplGlfw_InitForOpenGL(window.handle(), true);
		ASSERT(glfwResult, "ImGui GLFW backend failed to initialize");

		bool openglResult = ImGui_ImplOpenGL3_Init();
		ASSERT(openglResult, "ImGui OpenGL3 backend failed to initialize");

		Logger::info("[ImGuiManager] Initialized");
	}

	ImGuiManager::~ImGuiManager()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiManager::beginFrame()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// Transparent fullscreen dockspace - doesn't cover the scene
		ImGuiWindowFlags dockFlags =
			ImGuiWindowFlags_NoBackground |
			ImGuiWindowFlags_NoBringToFrontOnFocus;

		// PassthruCentralNode - makes the central empty area transparent - 3D scene shwos through
		ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);
	}

	void ImGuiManager::endFrame()
	{
		for (auto& panel : m_panels)
			panel->draw();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiManager::registerDefaultPanels()
	{
		addPanel(std::make_unique<DebugPanel>());
		addPanel(std::make_unique<LogPanel>());
	}

	void ImGuiManager::addPanel(std::unique_ptr<Panel> panel)
	{
		// TODO: look more into vector functionality + std::move()
		m_panels.push_back(std::move(panel));
	}

}