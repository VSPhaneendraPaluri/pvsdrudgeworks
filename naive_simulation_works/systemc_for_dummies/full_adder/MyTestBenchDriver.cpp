#include "MyTestBenchDriver.h"

void MyTestBenchDriver::Generate_Patterns()
{
	wait(5,SC_NS);
	sc_uint<3> cstInput;
	cstInput = 0;

	while(1)
	{
		TBDriver_a	=	cstInput[2];
		TBDriver_b	=	cstInput[1];
		TBDriver_c	=	cstInput[0];
		wait(5, SC_NS);		
		cstInput++;
	}
}
