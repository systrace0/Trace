#include "Logger.h"

#include <iostream>
#include <chrono>

#ifdef _WIN32
#include <windows.h>
#endif

namespace
{
	// Helper function to get the current time formatted as a string
	static std::string get_timestamp()
	{
		auto const time = std::chrono::current_zone()->to_local(std::chrono::system_clock::now());
		return std::format("{:%Y-%m-%d %X}", time);
	}
}

namespace engine
{
	// ANSI escape codes for terminal colors
	constexpr std::string_view COLOR_RESET = "\033[0m";
	constexpr std::string_view COLOR_GREEN = "\033[32m";
	constexpr std::string_view COLOR_YELLOW = "\033[33m";
	constexpr std::string_view COLOR_RED = "\033[31m";

	void Logger::init()
	{
#ifdef _WIN32
		// Grab the console output handle
		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		if (hOut == INVALID_HANDLE_VALUE) return;

		// Get the current console mode
		DWORD dwMode = 0;
		if (!GetConsoleMode(hOut, &dwMode)) return;

		// Enable Virtual Terminal Processing (ANSI colors)
		dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
		SetConsoleMode(hOut, dwMode);
#endif
	}


	void Logger::print_info(std::string_view message)
	{
		std::cout << COLOR_GREEN << "[" << get_timestamp() << "] [INFO]: " << message << COLOR_RESET << '\n';
	}

	void Logger::print_warn(std::string_view message)
	{
		std::cout << COLOR_YELLOW << "[" << get_timestamp() << "] [WARN]: " << message << COLOR_RESET << '\n';
	}

	void Logger::print_error(std::string_view message)
	{
		std::cerr << COLOR_RED << "[" << get_timestamp() << "] [ERROR]: " << message << COLOR_RESET << '\n';
	}
}