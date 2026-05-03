#include "DebugPanel.h"

#include <imgui.h>

namespace trace
{
	DebugPanel::DebugPanel()
		: m_glVersion((const char*)glGetString(GL_VERSION))
		, m_vendor((const char*)glGetString(GL_VENDOR))
		, m_renderer((const char*)glGetString(GL_RENDERER))
		, m_glsl((const char*)glGetString(GL_SHADING_LANGUAGE_VERSION))
	{
	}

	void DebugPanel::draw()
	{
		// -- Frame timing -----------------------------------------------------------------
		auto now = Clock::now();
		m_frameTimeMs = std::chrono::duration<float, std::milli>(now - m_lastFrame).count();
		m_lastFrame = now;

		float instantFps = (m_frameTimeMs > 0.0f) ? (1000.0f / m_frameTimeMs) : 0.0f;
		m_fpsSmoothed = m_fpsSmoothed * 0.9f + instantFps * 0.1f;

		m_frameTimeMin = std::min(m_frameTimeMin, m_frameTimeMs);
		m_frameTimeMax = std::max(m_frameTimeMax, m_frameTimeMs);

		m_frameTimeHistory[m_historyOffset] = m_frameTimeMs;
		m_historyOffset = (m_historyOffset + 1) % kHistorySize;

		// -- ImGui implementation ---------------------------------------------------------
		ImGui::Begin("Debug", nullptr, ImGuiWindowFlags_NoCollapse);

		ImGui::Text("%.1f FPS (%.2f ms/frame)", m_fpsSmoothed, m_frameTimeMs);
		ImGui::TextDisabled("min: %.2f ms   max: %.2f ms", m_frameTimeMin, m_frameTimeMax);

		if (ImGui::SmallButton("Reset min/max"))
		{
			m_frameTimeMin = 9999.0f;
			m_frameTimeMax = 0.0f;
		}

		// Frame-time history as a line graph
		ImGui::PlotLines("##ft",
			m_frameTimeHistory.data(),
			kHistorySize,
			m_historyOffset,
			std::format("{:.2f} ms", m_frameTimeMs).c_str(),
			0.0f, 40.0f,
			{ 0, 60 }
		);

		ImGui::Separator();

		if (ImGui::CollapsingHeader("OpenGL", ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::Text("Vendor: %s", m_vendor);
			ImGui::Text("GPU: %s", m_renderer);
			ImGui::Text("GL Version: %s", m_glVersion);
			ImGui::Text("GLSL:     %s", m_glsl);
		}

		ImGui::Separator();

		if (ImGui::CollapsingHeader("ImGui"))
		{
			ImGuiIO& io = ImGui::GetIO();
			ImGui::Text("ImGui %s", ImGui::GetVersion());
			ImGui::Text("Display: %.0f × %.0f px", io.DisplaySize.x, io.DisplaySize.y);
			ImGui::Text("Vertices: %d Indices: %d",
				ImGui::GetDrawData() ? ImGui::GetDrawData()->TotalVtxCount : 0,
				ImGui::GetDrawData() ? ImGui::GetDrawData()->TotalIdxCount : 0);

			// Temporary - just for exploring for future widgets
			ImGui::Checkbox("Show Demo Window", &m_showDemo);
			if (m_showDemo) ImGui::ShowDemoWindow(&m_showDemo);
		}

		ImGui::End();
	}
}