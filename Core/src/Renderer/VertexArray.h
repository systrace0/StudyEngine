#pragma once

#include "Core/Defines.h"

#include <glad/glad.h>

namespace trace
{
	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

		VertexArray(const VertexArray&) = delete;
		VertexArray& operator=(const VertexArray&) = delete;

		VertexArray(VertexArray&& other) noexcept;
		VertexArray& operator=(VertexArray&& other) noexcept;

		void bind() const;
		void unbind() const;

		[[nodiscard]] GLuint id() const { return m_id; }

		void setIndexCount(U32 count) { m_indexCount = count; }
		[[nodiscard]] U32 indexCount() const { return m_indexCount; }

	private:
		GLuint m_id{ 0 };
		U32 m_indexCount{ 0 };
	};
}