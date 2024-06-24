//INCLUDE EXTERNAL REFERENCES
#include "../Include/Framework.h"
#include <stdio.h>

//INITILIZING FRAMEWORK
int Framework::Init()
{
	//RETURN VALID
	return 1;
}

//UPDATE FRAMEWORK EVERY FRAME
int Framework::Update()
{
	printf("Hello World");
	//RETURN VALID
	return 1;
}

//TERMINATE FRAMEWORK
int Framework::Terminate()
{
	//RETURN VALID
	return 1;
}
