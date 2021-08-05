#include "texture.h"

#include <iostream>
#include "../../vendor/stb_image/stb_image.h"

namespace Core
{
	Texture::Texture(const std::string& path)
		: _textureId(0), _filepath(path), _localBuffer(nullptr), _width(0), _height(0), _nrChannels(0)
	{
		stbi_set_flip_vertically_on_load(1);
		this->_localBuffer = stbi_load(path.c_str(), &this->_width, &this->_height, &this->_nrChannels, 4);

		glGenTextures(1, &this->_textureId);
		
		if (this->_localBuffer) {
			GLenum format = GL_RGBA;
			if (this->_nrChannels == 1)
				format = GL_RED;
			else if (this->_nrChannels == 3)
				format = GL_RGB;

			glBindTexture(GL_TEXTURE_2D, this->_textureId);
			glTexImage2D(GL_TEXTURE_2D, 0, format, this->_width, this->_height, 0, format, GL_UNSIGNED_BYTE, this->_localBuffer);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

			stbi_image_free(this->_localBuffer);
		}
		else {
			std::cout << "Failed to load a texture from with path: " << _filepath << std::endl;
		}
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &this->_textureId);
	}

	void Texture::set(unsigned int slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, this->_textureId);
	}

	void Texture::unset() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
