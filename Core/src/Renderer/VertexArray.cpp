#include "Renderer/VertexArray.h"
#include "Core/Defines.h"
#include "Core/Logger.h"

namespace trace
{
	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &m_id);
		ASSERT(m_id != 0, "Failed to generate VAO");
	}

	VertexArray::~VertexArray()
	{
		if (m_id)
			glDeleteVertexArrays(1, &m_id);
	}

	VertexArray::VertexArray(VertexArray&& other) noexcept
		: m_id(other.m_id)
	{
		other.m_id = 0;
	}

	VertexArray& VertexArray::operator=(VertexArray&& other) noexcept
	{
		if (this != &other)
		{
			if (m_id)
				glDeleteVertexArrays(1, &m_id);
			m_id = other.m_id;
			other.m_id = 0;
		}

		return *this;
	}

	void VertexArray::bind() const
	{
		ASSERT(m_id != 0, "Calling bind() on uninitialized VAO");
		glBindVertexArray(m_id);
	}

	void VertexArray::unbind() const
	{
		glBindVertexArray(0);
	}
}