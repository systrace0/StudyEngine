#include "LogPanel.h"

#include <imgui.h>

// -- Sanity checks --------------------------------------------------------------------------------
static_assert((int)trace::LogLevel::Count == 6, "Update LogPanel filter array");

namespace trace
{
	std::vector<LogEntry> LogPanel::s_entries;

	void LogPanel::push(const LogEntry& entry)
	{
		s_entries.push_back(entry);

		if (s_entries.size() > 2000)
			s_entries.erase(s_entries.begin(), s_entries.begin() + 500);
	}

	void LogPanel::draw()
	{
		ImGui::Begin("Log", nullptr, ImGuiWindowFlags_NoCollapse);

		// -- Colors -------------------------------------------------------------------------
		const ImVec4 buttonColors[] = {
			{ 0.4f, 0.4f, 0.4f, 1.0f },  // Debug   — grey button
			{ 0.2f, 0.4f, 0.8f, 1.0f },  // Info    — blue button
			{ 0.7f, 0.5f, 0.0f, 1.0f },  // Warn    — dark yellow button
			{ 0.8f, 0.1f, 0.1f, 1.0f },  // Error   — red button
			{ 0.6f, 0.2f, 0.8f, 1.0f },  // Fatal   — purple button
			{ 0.0f, 0.6f, 0.2f, 1.0f },  // Success — dark green button
		};

		const ImVec4 textColors[] = {
			{ 0.6f, 0.6f, 0.6f, 1.0f },  // Debug   — grey text
			{ 1.0f, 1.0f, 1.0f, 1.0f },  // Info    — white text
			{ 1.0f, 0.8f, 0.0f, 1.0f },  // Warn    — yellow text
			{ 1.0f, 0.3f, 0.3f, 1.0f },  // Error   — red text
			{ 0.8f, 0.4f, 1.0f, 1.0f },  // Fatal   — light purple text
			{ 0.0f, 0.9f, 0.4f, 1.0f },  // Success — green text
		};

		const char* levelLabels[] = { "DEBUG", "INFO", "WARN", "ERROR", "FATAL", "SUCCESS" };

		// -- Filter Buttons -----------------------------------------------------------------
		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 3.0f);
		for (int i = 0; i < (int)LogLevel::Count; ++i)
		{
			// Inactive buttons
			ImVec4 color = m_levelFilter[i]
				? buttonColors[i]
				: ImVec4(0.2f, 0.2f, 0.2f, 1.0f);

			ImGui::PushStyleColor(ImGuiCol_Button, color);
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, color);
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, color);

			if (ImGui::Button(levelLabels[i]))
				m_levelFilter[i] = !m_levelFilter[i];

			ImGui::PopStyleColor(3);

			if (i < (int)LogLevel::Count - 1)
				ImGui::SameLine();
		}
		ImGui::PopStyleVar();

		ImGui::SameLine();
		ImGui::SetNextItemWidth(150.0f);  // fixed width, adjust to taste
		ImGui::InputText("##search", m_searchBuffer, sizeof(m_searchBuffer));
		ImGui::SameLine();
		ImGui::Checkbox("Auto-Scroll", &m_autoScroll);
		ImGui::SameLine();
		if (ImGui::Button("Clear")) s_entries.clear();

		ImGui::Separator();

		// Creates a scrollable box, height = 0 fill remaining window space
		ImGui::BeginChild("LogEntries", ImVec2(0, 0), false);

		for (auto& entry : s_entries)
		{
			// Skip if levels is filtered out
			if (!m_levelFilter[(int)entry.level])
				continue;

			// Skip if search doesn't match (case sensitive for now)
			if (m_searchBuffer[0] != '\0' && entry.message.find(m_searchBuffer) == std::string::npos)
				continue;

			ImGui::TextDisabled("[%s]", entry.timestamp.c_str());
			ImGui::SameLine();
			ImGui::PushStyleColor(ImGuiCol_Text, textColors[(int)entry.level]);
			ImGui::Text("[%s]", levelLabels[(int)entry.level]);
			ImGui::SameLine();
			ImGui::TextWrapped("%s", entry.message.c_str());
			ImGui::PopStyleColor();
		}

		// Auto scroll to bottom
		if (m_autoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY() - 4.0f)
			ImGui::SetScrollHereY(1.0f);

		ImGui::EndChild();
		ImGui::End();
	}
}