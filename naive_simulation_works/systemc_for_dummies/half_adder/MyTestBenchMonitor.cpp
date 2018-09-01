#include <systemc.h>
#include "MyTestBenchMonitor.h"

void MyTestBenchMonitor::Display_Patterns()
{
	cout << "At time : " << sc_time_stamp();
	cout << "\ta = " << TBMonitor_a << "\tb = " << TBMonitor_b;
	cout << "\tCarry = " << TBMonitor_carry << "\tSum = " << TBMonitor_sum << endl;
}

