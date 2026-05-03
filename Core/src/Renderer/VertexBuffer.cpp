#include "Renderer/VertexBuffer.h"
#include "Core/Defines.h"
#include "Core/Logger.h"

namespace trace
{
	VertexBuffer::VertexBuffer(const void* data, size_t sizeInBytes, GLenum usage)
	{
		glGenBuffers(1, &m_id);
		ASSERT(m_id != 0, "Failed to generate VBO");
		glBindBuffer(GL_ARRAY_BUFFER, m_id);
		glBufferData(GL_ARRAY_BUFFER, sizeInBytes, data, usage);
	}

	VertexBuffer::~VertexBuffer()
	{
		if (m_id)
			glDeleteBuffers(1, &m_id);
	}

	VertexBuffer::VertexBuffer(VertexBuffer&& other) noexcept
		: m_id(other.m_id)
	{
		other.m_id = 0;
	}

	VertexBuffer& VertexBuffer::operator=(VertexBuffer&& other) noexcept
	{
		if (this != &other)
		{
			if (m_id)
				glDeleteBuffers(1, &m_id);
			m_id = other.m_id;
			other.m_id = 0;
		}

		return *this;
	}

	void VertexBuffer::bind() const
	{
		ASSERT(m_id != 0, "Calling bind() on uninitialized VBO");
		glBindBuffer(GL_ARRAY_BUFFER, m_id);
	}

	void VertexBuffer::unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}