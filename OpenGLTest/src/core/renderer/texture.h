#pragma once

#include "renderer.h"
#include <string>

namespace Core
{
	class Texture {
	private:
		unsigned int _textureId;
		std::string _filepath;
		unsigned char* _localBuffer;
		int _width, _height, _nrChannels;
	public:
		Texture(const std::string& path);
		~Texture();

		void set(unsigned int slot = 0) const;
		void unset() const;

		inline int getWidth() const { return this->_width; }
		inline int getHeight() const { return this->_height; }

		// probably shouldn't be needed
		inline unsigned int getTextureId() const { return this->_textureId; }
	};
}
