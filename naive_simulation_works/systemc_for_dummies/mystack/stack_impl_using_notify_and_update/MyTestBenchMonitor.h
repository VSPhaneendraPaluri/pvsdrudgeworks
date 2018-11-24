#ifndef MYTESTBENCHMONITOR_H
#define MYTESTBENCHMONITOR_H

#include <systemc.h>

SC_MODULE(MyTestBenchMonitor)
{
	sc_in<int >	TBM_M, TBM_S;

	void Display_Patterns(void);

	SC_CTOR(MyTestBenchMonitor)
	{
		SC_METHOD(Display_Patterns);
			sensitive << TBM_M << TBM_S;
	}
};

#endif	// End of MYTESTBENCHMONITOR_H



