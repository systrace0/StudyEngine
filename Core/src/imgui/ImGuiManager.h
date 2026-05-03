#pragma once

#include "ImGui/Panel.h"
#include "Window/Window.h"

#include "imgui.h"

#include <vector>
#include <memory>

namespace trace
{
	class ImGuiManager
	{
	public:
		ImGuiManager(Window& window);
		~ImGuiManager();

		void beginFrame();
		void endFrame();

		void registerDefaultPanels();

		// TODO: Look up unique_ptr on cppreference
		void addPanel(std::unique_ptr<Panel> panel);

	private:
		std::vector<std::unique_ptr<Panel>> m_panels;
	};
}