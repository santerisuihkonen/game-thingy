#include "vertex-array.h"

namespace Core
{
	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &this->_rendererId);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &this->_rendererId);
	}

	void VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
	{
		this->set();
		vb.set();
		const auto& elements = layout.getElements();
		unsigned int offset = 0;
		for (unsigned int i = 0; i < elements.size(); i++) {
			const auto& element = elements[i];
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void*)offset);
			offset += element.count * VertexBufferElement::getSizeOfType(element.type);
		}
	}

	void VertexArray::set() const
	{
		glBindVertexArray(this->_rendererId);
	}

	void VertexArray::unset() const
	{
		glBindVertexArray(0);
	}
}
