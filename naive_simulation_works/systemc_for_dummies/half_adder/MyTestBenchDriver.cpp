#include <systemc.h>
#include "MyTestBenchDriver.h"

void MyTestBenchDriver::Generate_Patterns()
{
	sc_uint<2> cstInput;
	cstInput = 0;

	while(1)
	{
		TBDriver_a	=	cstInput[1];
		TBDriver_b	=	cstInput[0];
		wait(5, SC_NS);		
		cstInput++;
	}
}
