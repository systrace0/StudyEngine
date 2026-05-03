#pragma once

#include "Core/Defines.h"
#include <string>

#include <glad/glad.h>

namespace trace
{
	class Shader
	{
	public:
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
		void setFloat(const std::string& name, F32 value) const;
		void setMat4(const std::string& name, const F32* value) const;

	private:
		GLuint m_programID{ 0 };
	};
}
