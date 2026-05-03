#include "Renderer/Shader.h"
#include "Core/Logger.h"

#include <fstream>
#include <iostream>
#include <sstream>

// Anonymous namespace - free function that doesn't touch member variables etc.
// Invisible outside of Shader.cpp & caller doesn't need to know about it
namespace
{
	GLuint compileShader(GLenum type, const std::string& source, const std::string& name)
	{
		// OpenGL is a C API — can't pass std::string directly
		// c_str() gives us a null-terminated const char* it understands
		const char* src = source.c_str();
		GLuint shader = glCreateShader(type);

		// passing nullptr tells GL to measure string length itself (assumes
		// null-terminated)
		glShaderSource(shader, 1, &src, nullptr);

		glCompileShader(shader);

		GLint shader_compiled;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_compiled);
		if (shader_compiled != GL_TRUE)
		{
			GLsizei log_length = 0;
			std::string message;
			message.resize(1024);
			glGetShaderInfoLog(shader, static_cast<GLsizei>(message.size()), &log_length, &message[0]);
			message.resize(log_length > 0 ? static_cast<size_t>(log_length) : 0);
			glDeleteShader(shader); // Delete shader so the object doesn't leak on the GPU
			throw std::runtime_error(std::string("Shader compilation failed (") + name + "):\n" + message);
		}

		return shader;
	}
} // namespace

namespace trace
{
	Shader::Shader(const char* vertexPath, const char* fragmentPath)
	{
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
			throw std::runtime_error(std::string("Shader file read failed: ") +
				e.what());
		}

		// Provide the shader file paths as names so error messages are informative
		GLuint vertex = ::compileShader(GL_VERTEX_SHADER, vertexCode, vertexPath);
		GLuint fragment = ::compileShader(GL_FRAGMENT_SHADER, fragmentCode, fragmentPath);

		m_programID = glCreateProgram();

		glAttachShader(m_programID, vertex);
		glAttachShader(m_programID, fragment);
		glLinkProgram(m_programID);

		GLint program_linked;
		glGetProgramiv(m_programID, GL_LINK_STATUS, &program_linked);
		if (program_linked != GL_TRUE)
		{
			GLsizei log_length = 0;
			GLchar message[1024];
			glGetProgramInfoLog(m_programID, 1024, &log_length, message);
			glDeleteShader(vertex);
			glDeleteShader(fragment);
			glDeleteProgram(m_programID);
			throw std::runtime_error(std::string("Program linking failed:\n") +
				message);
		}

		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}

	Shader::~Shader()
	{
		if (m_programID)
		{
			glDeleteProgram(m_programID);
		}
	}

	Shader::Shader(Shader&& other) noexcept
		: m_programID(other.m_programID)
	{
		other.m_programID = 0;
	}

	Shader& Shader::operator=(Shader&& other) noexcept
	{
		if (this != &other)
		{
			if (m_programID)
				glDeleteProgram(m_programID);
			m_programID = other.m_programID;
			other.m_programID = 0;
		}
		return *this;
	}

	void Shader::use() const
	{
		ASSERT(m_programID != 0, "Calling use() on uninitialized shader");
		glUseProgram(m_programID);
	}

	void Shader::setBool(const std::string& name, bool value) const
	{
		ASSERT(m_programID != 0, "Calling setBool() on uninitialized shader");
		glUniform1i(glGetUniformLocation(m_programID, name.c_str()), (int)value);
	}

	void Shader::setInt(const std::string& name, int value) const
	{
		ASSERT(m_programID != 0, "Calling setInt() on uninitialized shader");
		glUniform1i(glGetUniformLocation(m_programID, name.c_str()), value);
	}

	void Shader::setFloat(const std::string& name, F32 value) const
	{
		ASSERT(m_programID != 0, "Calling setFloat() on uninitialized shader");
		glUniform1f(glGetUniformLocation(m_programID, name.c_str()), value);
	}

	void Shader::setMat4(const std::string& name, const F32* value) const
	{
		ASSERT(m_programID != 0, "Calling setMat4() on uninitialized shader");
		glUniformMatrix4fv(glGetUniformLocation(m_programID, name.c_str()), 1, GL_FALSE, value);
	}

} // namespace trace