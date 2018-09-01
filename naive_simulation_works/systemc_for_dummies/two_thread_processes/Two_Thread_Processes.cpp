#include <systemc.h>
#include "Two_Thread_Processes.h"

void Two_Thread_Processes::First_Thread(void)
{
	while(true)
	{
		wait(1.5, SC_NS);
		cout << "First Thread Starts @" << sc_time_stamp() << endl;
		wait(1.5, SC_NS);
		cout << "First Thread Stops @" << sc_time_stamp() << endl;
	}
}

void Two_Thread_Processes::Second_Thread(void)
{
	while(true)
	{
		wait(1, SC_NS);
		cout << "Second Thread Starts @" << sc_time_stamp() << endl;
		wait(1, SC_NS);
		cout << "Second Thread Stops @" << sc_time_stamp() << endl;
	}
}
