#include "MyTestBenchDriver.h"

void MyTestBenchDriver::Generate_Patterns()
{
	int i;

	while(1)
	{
		if(i < 10)
		{
			TBD_a.write(i);
			i++;
		}
		else
			break;
		
		wait(5.0, SC_NS);
	}
}
