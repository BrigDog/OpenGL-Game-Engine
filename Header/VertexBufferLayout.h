#pragma once
#include <vector>
#include "Constants.h"

struct VertexBufferElement 
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GetSize(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT: return 4;
		case GL_UNSIGNED_BYTE: return 1;
		case GL_UNSIGNED_INT: return 4;
		}
		CHECK(false);
		return -1;
	}

};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride;
public:
	void Settup()
	{
		m_Stride = 0;
	}

	template<typename T>
	void Push(unsigned int count)
	{
		//CHECK(false);
	}
	template<>
	void Push<float>(unsigned int count)
	{
		VertexBufferElement m_Element;
		m_Element.type = GL_FLOAT;
		m_Element.count = count;
		m_Element.normalized = GL_FALSE;
		m_Elements.push_back(m_Element);
		m_Stride += VertexBufferElement::GetSize(GL_FLOAT) * count;
	}
	template<>
	void Push<unsigned int>(unsigned int count)
	{
		VertexBufferElement m_Element;
		m_Element.type = GL_UNSIGNED_INT;
		m_Element.count = count;
		m_Element.normalized = GL_FALSE;
		m_Elements.push_back(m_Element);
		m_Stride += VertexBufferElement::GetSize(GL_UNSIGNED_INT) * count;
	}
	template<>
	void Push<unsigned char>(unsigned int count)
	{
		VertexBufferElement m_Element;
		m_Element.type = GL_UNSIGNED_BYTE;
		m_Element.count = count;
		m_Element.normalized = GL_TRUE;
		m_Elements.push_back(m_Element);
		m_Stride += VertexBufferElement::GetSize(GL_UNSIGNED_BYTE) * count;
	}
	inline const std::vector<VertexBufferElement> GetElements() const { return m_Elements; }
	inline unsigned int GetStride() const { return m_Stride; }
};