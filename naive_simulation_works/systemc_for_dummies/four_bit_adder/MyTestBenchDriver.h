#ifndef MYTESTBENCHDRIVER_H
#define MYTESTBENCHDRIVER_H

#include <systemc.h>

SC_MODULE(MyTestBenchDriver)
{
	sc_out<sc_lv<1> >	TBD_a[4], TBD_b[4];

	void Generate_Patterns(void);

	SC_CTOR(MyTestBenchDriver)
	{
		SC_THREAD(Generate_Patterns);
	}
};

#endif // End of MYTESTBENCHDRIVER_H
