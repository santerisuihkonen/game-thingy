#include "index-buffer.h"

#include "renderer.h"

namespace Core
{
    IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
        : _count(count)
    {
        ASSERT(sizeof(unsigned int) == sizeof(GLuint));

        glGenBuffers(1, &this->_rendererId);
        this->set();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
    }

    IndexBuffer::~IndexBuffer()
    {
        glDeleteBuffers(1, &this->_rendererId);
    }

    void IndexBuffer::set() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_rendererId);
    }

    void IndexBuffer::unset() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

}