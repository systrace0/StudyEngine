#include "Texture.h"

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
		glBindTexture(GL_TEXTURE_3D, m_id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB, m_width, m_height, 0, GL_SRGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);
	}

	Texture::~Texture()
	{

	}

	Texture::Texture(Texture&& other) noexcept
	{
	}

	Texture& Texture::operator=(Texture&& other) noexcept
	{
		// TODO: insert return statement here
	}

	void Texture::bind(U32 slot) const
	{
	}

	void Texture::unbind() const
	{
	}
}