//DECLARE ONLY ONCE
#pragma once

#include "Window.h"

//DEFINING FRAMEWORK
class Framework
{
	//DEFINING ALL PUBLIC VARIABLES
public:
	//DEFINING INITILIZING
	int Init();
	//DEFINING UPDATE
	int Update();
	//DEFINING TERMINATION
	int Terminate();
	//DEFINING ALL PRIVATE VARIABLES
private:
	Window m_Window;
};
