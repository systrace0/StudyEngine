#pragma once

#include "ImGui/Panel.h"
#include "Core/LogEntry.h"

#include <vector>

namespace trace
{
	class LogPanel : public Panel
	{
	public:
		static void push(const LogEntry& entry);
		static void   clear() { s_entries.clear(); }
		static size_t entryCount() { return s_entries.size(); }
		void draw() override;

	private:
		static std::vector<LogEntry> s_entries;
		bool m_levelFilter[(int)LogLevel::Count]{ true, true, true, true, true, true };
		bool m_autoScroll = true;
		char m_searchBuffer[256]{}; // ImGui search input
	};
}