#pragma once

#include "Constants.h"

class IndexBuffer
{
public:
	~IndexBuffer();
	void Settup(const unsigned int* data, unsigned int count);
	void Bind() const;
	void Unbind() const;

	inline unsigned int GetCount() const { return M_Count; }
private:
	unsigned int RenderID;
	unsigned int M_Count;
};