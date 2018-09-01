#include "MyTestBenchMonitor.h"

void MyTestBenchMonitor::Display_Patterns()
{
	cout << "At time : " << sc_time_stamp();
	//next_trigger(TBMonitor_a. | TBMonitor_b | TBMonitor_c);	
	cout << "\ta = " << TBMonitor_a << "\tb = " << TBMonitor_b << "\tc_in = " << TBMonitor_c;
	//next_trigger(TBMonitor_sum | TBMonitor_sum);
	cout << "\tCarry = " << TBMonitor_carry << "\tSum = " << TBMonitor_sum << endl;
}

