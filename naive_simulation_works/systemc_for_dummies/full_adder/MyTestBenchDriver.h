#ifndef MYTESTBENCHDRIVER_H
#define MYTESTBENCHDRIVER_H

#include <systemc.h>

SC_MODULE(MyTestBenchDriver)
{
	sc_out<bool>	TBDriver_a, TBDriver_b, TBDriver_c;

	void Generate_Patterns(void);

	SC_CTOR(MyTestBenchDriver)
	{
		SC_THREAD(Generate_Patterns);
	}
};

#endif // End of MYTESTBENCHDRIVER_H
