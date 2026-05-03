#include "Renderer/IndexBuffer.h"
#include "Core/Defines.h"
#include "Core/Logger.h"

namespace trace
{
	IndexBuffer::IndexBuffer(const U32* data, U32 count)
	{
		glGenBuffers(1, &m_id);
		ASSERT(m_id != 0, "Failed to generate EBO");
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(U32), data, GL_STATIC_DRAW);
	}

	IndexBuffer::~IndexBuffer()
	{
		if (m_id)
			glDeleteBuffers(1, &m_id);
	}

	IndexBuffer::IndexBuffer(IndexBuffer&& other) noexcept
		: m_id(other.m_id)
	{
		other.m_id = 0;
	}


	IndexBuffer& IndexBuffer::operator=(IndexBuffer&& other) noexcept
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

	void IndexBuffer::bind() const
	{
		ASSERT(m_id != 0, "Calling bind() on uninitialized EBO");
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
	}

	void IndexBuffer::unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}