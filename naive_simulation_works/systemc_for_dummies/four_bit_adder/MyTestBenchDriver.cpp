#include "MyTestBenchDriver.h"

void MyTestBenchDriver::Generate_Patterns()
{
	int i;

	wait(5.0, SC_NS);
	
	// Initialize test bench inputs to all zeros
	for(i=0; i < 4; i++)
	{
		TBD_a[i] = 0;
		TBD_b[i] = 0;
	}

	i = 0;

	while(1)
	{
		wait(5.0, SC_NS);
		if(i < 4)
		{
			TBD_a[i] = 1;
			TBD_b[i] = 1;
			i++;
		}
		else
			break;
	}
}
