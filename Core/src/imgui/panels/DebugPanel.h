#pragma once

#include "ImGui/Panel.h"

#include <chrono>
#include <array>

namespace trace
{
	class DebugPanel : public Panel
	{
	public:
		DebugPanel();
		void draw() override;

	private:
		using Clock = std::chrono::steady_clock;
		using TimePoint = Clock::time_point;

		const char* m_glVersion{ nullptr };
		const char* m_vendor{ nullptr };
		const char* m_renderer{ nullptr };
		const char* m_glsl{ nullptr };

		static constexpr int kHistorySize = 128;

		TimePoint m_lastFrame{ Clock::now() };
		float m_frameTimeMs{ 0.0f };
		float m_fpsSmoothed{ 0.0f };
		float m_frameTimeMin{ 9999.0f };
		float m_frameTimeMax{ 0.0f };
		int m_historyOffset{ 0 };
		bool m_showDemo{ false };
		std::array<float, kHistorySize> m_frameTimeHistory{};
	};
}
