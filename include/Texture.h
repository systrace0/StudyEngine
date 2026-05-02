#pragma once

#include "glad/glad.h"

#include "Core.h"

namespace trace
{
	class Texture
	{
	public:
		Texture(const char* path);
		~Texture();

		Texture(const Texture&) = delete;
		Texture& operator=(const Texture&) = delete;

		Texture(Texture&& other) noexcept;
		Texture& operator=(Texture&& other) noexcept;

		void bind(U32 slot = 0) const;
		void unbind() const;

		[[nodiscard]] GLuint id()	  const { return m_id; };
		[[nodiscard]] int	 width()  const { return m_width; };
		[[nodiscard]] int	 height() const { return m_height; };

	private:
		GLuint m_id{ 0 };
		int	   m_width{};
		int    m_height{};
	};
}