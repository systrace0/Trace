#pragma once

#include <glad/glad.h>

namespace engine
{
	class Shader
	{
		Shader(const char* vertexPath, const char* fragmentPath);
		~Shader();

		Shader(const Shader&) = delete;
		Shader& operator=(const Shader&) = delete;

		Shader(Shader&& other) noexcept;
		Shader& operator=(Shader&& other) noexcept;

		void use() const;

		// Uniform setters
		void setBool(const char* name, bool value) const;
		void setInt(const char* name, int value) const;
		void setFloat(const char* name, float value) const;

	private:
		GLuint m_programID = 0;
		std::string
	};
}