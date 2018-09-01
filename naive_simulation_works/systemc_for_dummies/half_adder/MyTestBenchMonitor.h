#ifndef MYTESTBENCHMONITOR_H
#define MYTESTBENCHMONITOR_H

#include <systemc.h>

SC_MODULE(MyTestBenchMonitor)
{
	sc_in<bool>	TBMonitor_a, TBMonitor_b, TBMonitor_sum, TBMonitor_carry;

	void Display_Patterns(void);

	SC_CTOR(MyTestBenchMonitor)
	{
		SC_METHOD(Display_Patterns);
		sensitive << TBMonitor_a << TBMonitor_b << TBMonitor_sum << TBMonitor_carry;
		//sensitive << TBMonitor_sum << TBMonitor_carry;
	}
};

#endif	// End of MYTESTBENCHMONITOR_H



