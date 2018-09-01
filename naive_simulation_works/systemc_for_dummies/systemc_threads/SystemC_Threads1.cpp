#include <systemc.h>
#include "SystemC_Threads1.h"

void SystemC_Threads1::A_Thread()
{
	cout << "Entered Thread A @" << sc_time_stamp() << endl;
	while(1)
	{
		cout << "Thread A  Waiting for Event A @" << sc_time_stamp() << endl;
		wait();
		cout << "Thread A  Resume after  Event A @" << sc_time_stamp() << endl;
		cout << "Notify Event B after 1 NS   @" << sc_time_stamp() << endl;
		b_thread_event.notify(1, SC_NS);
		cout << "Pausing Thread A  for Event B @" << sc_time_stamp() << endl;
		wait(b_thread_event);
		cout << "Resumed Thread A  after Event B @" << sc_time_stamp() << endl;
	}
}


void SystemC_Threads1::B_Thread()
{
		cout << "Entered Thread B @" << sc_time_stamp() << endl;
	while(1)
	{
		cout << "Notify Event C after 1.5 NS   @" << sc_time_stamp() << endl;
		c_thread_event.notify(1.5, SC_NS);
		cout << "Pausing Thread B  for Event B @" << sc_time_stamp() << endl;
		wait();
		cout << "Resumed Thread B  After Event B @" << sc_time_stamp() << endl;
	}
}


void SystemC_Threads1::C_Thread()
{ 
		cout << "Entered Thread C @" << sc_time_stamp() << endl;
		cout << "Pausing Thread C  for Event C @" << sc_time_stamp() << endl;
	wait();
		cout << "Resumed Thread C  After Event C @" << sc_time_stamp() << endl;
	while(1)
	{
		cout << "Notify Event A after 0.5 NS   @" << sc_time_stamp() << endl;
		a_thread_event.notify(0.5, SC_NS);
		cout << "Pausing Thread C for Event B and C  @" << sc_time_stamp() << endl;
		wait(b_thread_event & c_thread_event);
		cout << "Resumed Thread C  After Event B and C @" << sc_time_stamp() << endl;
		cout << "Notify Event D after xx  NS   @" << sc_time_stamp() << endl;
		d_thread_event.notify();
		//cout << "Resumed Thread C @" << sc_time_stamp() << endl;
	}
}


void SystemC_Threads1::D_Thread()
{
	cout << "Entered Thread D @" << sc_time_stamp() << endl;
	wait();
	cout << "Leaving Thread D @" << sc_time_stamp() << endl;
}
