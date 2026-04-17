#include "Shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

// Anonymous namespace - free function that doesn't touch member variables etc.
// Invisible outside of Shader.cpp & caller doesn't need to know about it
namespace
{
	GLuint compileShader(GLenum type, const std::string& source)
	{
		// OpenGL is a C API — can't pass std::string directly
		// c_str() gives us a null-terminated const char* it understands
		const char* src = source.c_str();
		GLuint shader = glCreateShader(type);

		// passing nullptr tells GL to measure string length itself (assumes null-terminated)
		glShaderSource(shader, 1, &src, nullptr);

		glCompileShader(shader);

		GLint shader_compiled;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_compiled);
		if (shader_compiled != GL_TRUE)
		{
			GLsizei log_length = 0;
			GLchar message[1024];
			glGetShaderInfoLog(shader, 1024, &log_length, message);
			glDeleteShader(shader);
			throw std::runtime_error(std::string("Shader compilation failed:\n") + message);
		}

	}
}

namespace engine
{
	Shader::Shader(const char* vertexPath, const char* fragmentPath)
	{
		// TODO: stringstream could be replaced with std::string since it's faster through the iteration etc.
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;

		// ifstream keeps track of its state using flags.
		// this checks for the state of files wether it fails or is corrupted
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try
		{
			// Open File
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream, fShaderStream;

			// Read file's buffer contents into streams
			// Basically rdbuf gives acces to the file's character stream
			// And copies all those characters into stringstream
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();

			vShaderFile.close();
			fShaderFile.close();

			// Convert stream into string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::ifstream::failure& e)
		{
			throw std::runtime_error(
				std::string("Shader file read failed: ") + e.what()
			);
		}

	}

	Shader::~Shader()
	{
		if (m_programID)
			glDeleteProgram(m_programID);
	}

	void Shader::use() const
	{
		glUseProgram(m_programID);
	}

}