#include "Logger.h"

#include <iostream>

namespace engine
{
	void Logger::print_info(std::string_view message)
	{
		std::cout << "[INFO]: " << message << '\n';
	}

	void Logger::print_warn(std::string_view message)
	{
		std::cout << "[WARN]: " << message << '\n';
	}

	void Logger::print_error(std::string_view message)
	{
		std::cout << "[ERROR]: " << message << '\n';
	}
}