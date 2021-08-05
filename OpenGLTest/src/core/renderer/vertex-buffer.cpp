#include "vertex-buffer.h"

#include "renderer.h"

namespace Core
{
    VertexBuffer::VertexBuffer(const void* data, unsigned int size)
    {
        glGenBuffers(1, &this->_rendererId);
        glBindBuffer(GL_ARRAY_BUFFER, this->_rendererId);
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }

    VertexBuffer::~VertexBuffer()
    {
        glDeleteBuffers(1, &this->_rendererId);
    }

    void VertexBuffer::set() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, this->_rendererId);
    }

    void VertexBuffer::unset() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

}