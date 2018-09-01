#ifndef MYTESTBENCHMONITOR_H
#define MYTESTBENCHMONITOR_H

#include <systemc.h>

SC_MODULE(MyTestBenchMonitor)
{
	sc_in<sc_lv<1> >	TBM_a[4], TBM_b[4], TBM_z[5];

	void Display_Patterns(void);

	SC_CTOR(MyTestBenchMonitor)
	{
		SC_METHOD(Display_Patterns);
			sensitive << TBM_a[3] << TBM_a[2] << TBM_a[1] << TBM_a[0];
			sensitive << TBM_b[3] << TBM_b[2] << TBM_b[1] << TBM_b[0];
			sensitive << TBM_z[4] << TBM_z[3] << TBM_z[2] << TBM_z[1] << TBM_z[0];
	}
};

#endif	// End of MYTESTBENCHMONITOR_H



