#pragma once

#include "Core/Defines.h"

#include <glad/glad.h>

namespace trace
{
	class VertexBuffer
	{
	public:
		VertexBuffer(const void* data, size_t sizeInBytes, GLenum usage = GL_STATIC_DRAW);
		~VertexBuffer();

		VertexBuffer(const VertexBuffer&) = delete;
		VertexBuffer& operator=(const VertexBuffer&) = delete;

		VertexBuffer(VertexBuffer&& other) noexcept;
		VertexBuffer& operator=(VertexBuffer&& other) noexcept;

		void bind() const;
		void unbind() const;

		[[nodiscard]] GLuint id() const { return m_id; }

	private:
		GLuint m_id{ 0 };
	};
}