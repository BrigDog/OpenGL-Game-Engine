#include "../Header/IndexBuffer.h"

IndexBuffer::~IndexBuffer()
{
    CHECKFUNCTION(glDeleteBuffers(1, &RenderID));
}
void IndexBuffer::Settup(const unsigned int* data, unsigned int count)
{
    CHECK(sizeof(unsigned int) == sizeof(GLuint));
    M_Count = count;

    CHECKFUNCTION(glGenBuffers(1, &RenderID));
    CHECKFUNCTION(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, RenderID));
    CHECKFUNCTION(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}
void IndexBuffer::Bind() const
{
    CHECKFUNCTION(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, RenderID));
}
void IndexBuffer::Unbind() const
{
    CHECKFUNCTION(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}