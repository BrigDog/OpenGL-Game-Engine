#include "../Include/Framework.h"
#include <stdio.h>

int Framework::Init()
{
	return 1;
}

int Framework::Update()
{
	printf("Hello World");;;
	return 1;
}

int Framework::Terminate()
{
	return 1;
}
