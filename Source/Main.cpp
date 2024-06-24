//INCLUDE EXTERNAL REFERENCES
#include "../Include/Main.h"
#include <cassert>

//ENTRANCE POINT OF THE CODE
int main()
{
	//INITILIZE FRAMEWORK
	assert(M_Framework.Init() == true);
	//CREATE A INCOMPLETE VARIABLE
	bool Complete = 0;
	//LOOPS UNTIL PREVIOUS VARIABLE IS COMPLETE
	while (Complete == false)
	{
		//UPDATE FRAMEWORK AND ASSIGN THE RETURN VARIABLE
		Complete = M_Framework.Update();
	}
	//ASSERT TO MAKE SURE THERE IS NO BUGS
	assert(Complete == true);
	//TERMINATE FRAMEWORK
	assert(M_Framework.Terminate() == true);
	//COMPLETE THE PROGRAM
	return 1;
}