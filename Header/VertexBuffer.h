#pragma once

#include "Constants.h"

class VertexBuffer
{
public:
	~VertexBuffer();
	void Settup(const void* data, unsigned int count);
	void Bind() const;
	void Unbind() const;
private:
	unsigned int RenderID;
};