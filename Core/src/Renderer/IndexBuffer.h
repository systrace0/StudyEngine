#pragma once

#include "Core/Defines.h"

#include <glad/glad.h>

namespace trace
{
	class IndexBuffer
	{
	public:
		IndexBuffer(const U32* data, U32 count);
		~IndexBuffer();

		IndexBuffer(const IndexBuffer&) = delete;
		IndexBuffer& operator=(const IndexBuffer&) = delete;

		IndexBuffer(IndexBuffer&& other) noexcept;
		IndexBuffer& operator=(IndexBuffer&& other) noexcept;

		void bind() const;
		void unbind() const;

		[[nodiscard]] GLuint id() const { return m_id; }

	private:
		GLuint m_id{ 0 };
	};
}