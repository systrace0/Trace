#pragma once

#include <string>

namespace engine
{
	enum class LogLevel { Info, Warn, Error, Fatal, Success, Count };

	struct LogEntry
	{
		std::string message;
		std::string timestamp;
		LogLevel	level;
	};
}