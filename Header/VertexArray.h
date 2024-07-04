#pragma once

#include "Constants.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray
{
public:
	~VertexArray();
	void SettupVertexArray();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
	void Bind() const;
	void Unbind() const;
private:
	unsigned int m_RendererID;
};

//VertexArray::~VertexArray()
//{
//	CHECKFUNCTION(glDeleteVertexArrays(1, &m_RendererID));
//}

inline VertexArray::~VertexArray()
{
}

inline void VertexArray::SettupVertexArray()
{
	CHECKFUNCTION(glGenVertexArrays(1, &m_RendererID));
}

inline void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
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

inline void VertexArray::Bind() const
{
	CHECKFUNCTION(glBindVertexArray(m_RendererID));
}

inline void VertexArray::Unbind() const
{
	CHECKFUNCTION(glBindVertexArray(0));
}