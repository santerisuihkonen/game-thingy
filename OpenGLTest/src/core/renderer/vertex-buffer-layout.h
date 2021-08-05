#pragma once

#include <vector>
#include "renderer.h"

namespace Core
{
	struct VertexBufferElement {
		unsigned int type;
		unsigned int count;
		unsigned char normalized;

		static unsigned int getSizeOfType(unsigned int type) {
			switch (type)
			{
			case GL_FLOAT: return 4;
			case GL_UNSIGNED_INT: return 4;
			case GL_UNSIGNED_BYTE: return 1;
			}
			return 0;
		}
	};

	class VertexBufferLayout {
	private:
		std::vector<VertexBufferElement> _elements;
		unsigned int _stride;
	public:
		VertexBufferLayout()
			: _stride(0) {}

		template<typename T>
		void push(unsigned int count) {
			static_assert(false);
		}

		template<>
		void push<float>(unsigned int count) {
			this->_elements.push_back({ GL_FLOAT, count, GL_FALSE });
			this->_stride += VertexBufferElement::getSizeOfType(GL_FLOAT) * count;
		}

		template<>
		void push<unsigned int>(unsigned int count) {
			this->_elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
			this->_stride += VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT) * count;
		}

		template<>
		void push<unsigned char>(unsigned int count) {
			this->_elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
			this->_stride += VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE) * count;
		}

		inline const std::vector<VertexBufferElement> getElements() const { return this->_elements; }
		inline unsigned int getStride() const { return this->_stride; }
	};
}
