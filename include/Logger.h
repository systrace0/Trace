#pragma once

#include <format>
#include <string_view>

namespace engine
{
	// Stateless now — class kept intentionally for future state
	// (log file handle, level filtering, output redirection)
	class Logger
	{
	private:
		static void print_info(std::string_view message);
		static void print_warn(std::string_view message);
		static void print_error(std::string_view message);

	public:
		static void init();

		template<typename... Args>
		static void info(std::format_string<Args...> fmt, Args&&... args)
		{
			print_info(std::format(fmt, std::forward<Args>(args)...));
		}

		template <typename... Args>
		static void warn(std::format_string<Args...> fmt, Args&&... args)
		{
			print_warn(std::format(fmt, std::forward<Args>(args)...));
		}

		template <typename... Args>
		static void error(std::format_string<Args...> fmt, Args&&... args)
		{
			print_error(std::format(fmt, std::forward<Args>(args)...));
		}
	};
}