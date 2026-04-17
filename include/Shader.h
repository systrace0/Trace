#pragma once

#include <glad/glad.h>

#include <string>

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
		void setBool(const std::string& name, bool value) const;
		void setInt(const std::string& name, int value) const;
		void setFloat(const std::string& name, float value) const;
		void setMat4(const std::string& name, const float* value) const;

	private:
		GLuint m_programID = 0;
	};
}