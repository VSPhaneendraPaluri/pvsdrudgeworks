#include <systemc.h>
#include "Half_Adder.h"
#include "MyTestBenchDriver.h"
#include "MyTestBenchMonitor.h"

int sc_main(int sc_argc, char* sc_argv[])
{
	sc_signal<bool> pb_a, pb_b, pb_sum, pb_carry;

	Half_Adder MyHalfAdder("MyHalfAdder");
	MyHalfAdder.a(pb_a);
	MyHalfAdder.b(pb_b);
	MyHalfAdder.sum(pb_sum);
	MyHalfAdder.carry(pb_carry);

	MyTestBenchDriver MyTBDriver("MyTBDriver");
	MyTBDriver.TBDriver_a(pb_a);
	MyTBDriver.TBDriver_b(pb_b);

	MyTestBenchMonitor MyTBMonitor("MyTBMonitor");
	MyTBMonitor.TBMonitor_a(pb_a);
	MyTBMonitor.TBMonitor_b(pb_b);
	MyTBMonitor.TBMonitor_sum(pb_sum);
	MyTBMonitor.TBMonitor_carry(pb_carry);

	sc_set_time_resolution(1, SC_NS);
	sc_start(60.0, SC_NS);

	return 0;
}
