#include "Texture.h"
#include "Core/Defines.h"

#include "stb_image.h"

namespace trace
{
	Texture::Texture(const char* path)
	{
		int nrChannels{ 0 };

		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(path, &m_width, &m_height, &nrChannels, 0);

		if (!data)
			throw std::runtime_error(std::string("Failed to load texture: ") + path);

		glGenTextures(1, &m_id);
		glBindTexture(GL_TEXTURE_2D, m_id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);					// horizontal wrapping (S = X axis in UV space)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);					// Vertical	  wrapping (T = Y axis in UV space)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // Filtering when texture is smaller than screen
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);				// Filtering when texture is larger than screen

		GLenum format = GL_RGB;
		if (nrChannels == 1) format = GL_RED;
		if (nrChannels == 3) format = GL_RGB;
		if (nrChannels == 4) format = GL_RGBA;

		glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);

		Logger::info("[Texture] Loaded: {} ({}x{} channels:{})", path, m_width, m_height, nrChannels);
	}

	Texture::~Texture()
	{
		if (m_id)
			glDeleteTextures(1, &m_id);
	}

	Texture::Texture(Texture&& other) noexcept
		: m_id(other.m_id)
		, m_width(other.m_width)
		, m_height(other.m_height)
	{
		other.m_id = 0;
	}

	Texture& Texture::operator=(Texture&& other) noexcept
	{
		if (this != &other)
		{
			if (m_id)
				glDeleteTextures(1, &m_id);
			m_id = other.m_id;
			m_width = other.m_width;
			m_height = other.m_height;
			other.m_id = 0;
		}
		return *this;
	}

	void Texture::bind(U32 slot) const
	{
		ASSERT(m_id != 0, "Calling bind() on unitialized Texture");
		ASSERT(slot < 32, "Texture slot out of range (Max. 31)");
		glActiveTexture(GL_TEXTURE0 + slot); // Through GL_TEXTURE31
		glBindTexture(GL_TEXTURE_2D, m_id);
	}

	void Texture::unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}