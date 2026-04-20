#include "Logger.h"

#include <iostream>
#include <chrono>

namespace engine
{
	// ANSI escape codes for terminal colors
	constexpr std::string_view COLOR_RESET = "\033[0m";
	constexpr std::string_view COLOR_GREEN = "\033[32m";
	constexpr std::string_view COLOR_YELLOW = "\033[33m";
	constexpr std::string_view COLOR_RED = "\033[31m";

	// Helper function to get the current time formatted as a string
	static std::string get_timestamp()
	{
		auto const time = std::chrono::current_zone()->to_local(std::chrono::system_clock::now());
		return std::format("{:%Y-%m-%d %X}", time);
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
		std::cout << COLOR_RED << "[" << get_timestamp() << "] [ERROR]: " << message << COLOR_RESET << '\n';
	}
}