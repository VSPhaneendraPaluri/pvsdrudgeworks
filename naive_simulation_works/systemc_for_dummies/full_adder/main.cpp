#include <systemc.h>
#include "Full_Adder.h"
#include "MyTestBenchDriver.h"
#include "MyTestBenchMonitor.h"

int sc_main(int sc_argc, char* sc_argv[])
{
	sc_signal<bool> pb_a, pb_b, pb_c_in, pb_sum, pb_c_out;

	Full_Adder MyFullAdder("MyFullAdder");
	MyFullAdder.a(pb_a);
	MyFullAdder.b(pb_b);
	MyFullAdder.c_in(pb_c_in);
	MyFullAdder.sum_out(pb_sum);
	MyFullAdder.c_out(pb_c_out);

	MyTestBenchDriver MyTBDriver("MyTBDriver");
	MyTBDriver.TBDriver_a(pb_a);
	MyTBDriver.TBDriver_b(pb_b);
	MyTBDriver.TBDriver_c(pb_c_in);

	MyTestBenchMonitor MyTBMonitor("MyTBMonitor");
	MyTBMonitor.TBMonitor_a(pb_a);
	MyTBMonitor.TBMonitor_b(pb_b);
	MyTBMonitor.TBMonitor_c(pb_c_in);
	MyTBMonitor.TBMonitor_sum(pb_sum);
	MyTBMonitor.TBMonitor_carry(pb_c_out);

	sc_set_time_resolution(1, SC_NS);
	sc_start(100.0, SC_NS);

	return 0;
}
