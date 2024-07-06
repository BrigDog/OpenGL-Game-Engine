#include "../Header/VertexBuffer.h"

VertexBuffer::~VertexBuffer()
{
    CHECKFUNCTION(glDeleteBuffers(1, &RenderID));
}

void VertexBuffer::Settup(const void* data, unsigned int size)
{
    CHECKFUNCTION(glGenBuffers(1, &RenderID));
    CHECKFUNCTION(glBindBuffer(GL_ARRAY_BUFFER, RenderID));
    CHECKFUNCTION(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

void VertexBuffer::Bind() const
{
    CHECKFUNCTION(glBindBuffer(GL_ARRAY_BUFFER, RenderID));
}

void VertexBuffer::Unbind() const
{
    CHECKFUNCTION(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
