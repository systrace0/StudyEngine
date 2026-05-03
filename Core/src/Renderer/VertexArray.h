#pragma once

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

	private:
		GLuint m_id{ 0 };
	};
}