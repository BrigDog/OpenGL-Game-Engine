#include "../Include/Main.h"
#include <cassert>

int main()
{
	assert(M_Framework.Init() == true);
	bool Complete = 0;
	while (Complete == false)
	{
		Complete = M_Framework.Update();
	}
	assert(Complete == true);
	assert(M_Framework.Terminate() == true);
	return 1;
}