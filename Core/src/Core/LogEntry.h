#pragma once

#include <string>

namespace trace
{
	enum class LogLevel { Debug, Info, Warn, Error, Fatal, Success, Count };

	struct LogEntry
	{
		std::string message;
		std::string timestamp;
		LogLevel	level;
	};
}