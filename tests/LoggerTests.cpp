#include <gtest/gtest.h>

#include "Core/Logger.h"
#include "ImGui/panels/LogPanel.h"
#include "Renderer/Vertex.h"

// TODO: Fix glad build error

namespace trace
{
	TEST(LogPanel, PushAddsEntry)
	{
		trace::LogPanel::clear();
		trace::LogPanel::push({ "test message", "12:00:00", trace::LogLevel::Info });

		EXPECT_EQ(trace::LogPanel::entryCount(), 1);
	}

	TEST(LogPanel, RollingWindowCapsAt2000)
	{
		trace::LogPanel::clear();
		for (int i = 0; i < 2500; i++)
			trace::LogPanel::push({ "msg", "00:00:00", trace::LogLevel::Info });

		EXPECT_LE(trace::LogPanel::entryCount(), 2000);
	}

	TEST(LogPanel, FilterLevelSkipsEntry)
	{
		trace::LogPanel::clear();
		trace::LogPanel::push({ "debug msg", "00:00:00", trace::LogLevel::Debug });
		trace::LogPanel::push({ "info msg",  "00:00:00", trace::LogLevel::Info });

		EXPECT_EQ(trace::LogPanel::entryCount(), 2);
	}

	TEST(Vertex, LayoutNoPadding)
	{
		EXPECT_EQ(sizeof(trace::Vertex), 24);
		EXPECT_EQ(offsetof(trace::Vertex, color), 12);
	}
} // namespace trace