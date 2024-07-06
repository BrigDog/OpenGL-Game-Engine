#include "../Header/VertexArray.h"

VertexArray::~VertexArray()
{
	CHECKFUNCTION(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::SettupVertexArray()
{
	CHECKFUNCTION(glGenVertexArrays(1, &m_RendererID));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		CHECKFUNCTION(glEnableVertexAttribArray(i));
		CHECKFUNCTION(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset));
		offset += element.count * VertexBufferElement::GetSize(element.type);
	}
}

void VertexArray::Bind() const
{
	CHECKFUNCTION(glBindVertexArray(m_RendererID));
}

void VertexArray::Unbind() const
{
	CHECKFUNCTION(glBindVertexArray(0));
}
