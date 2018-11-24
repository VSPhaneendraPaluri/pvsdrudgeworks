#ifndef TWO_THREAD_PROCESSES_H
#define TWO_THREAD_PROCESSES_H

#include <systemc.h>

SC_MODULE (Two_Thread_Processes)
{
	void First_Thread(void);
	void Second_Thread(void);

	SC_CTOR (Two_Thread_Processes)
	{
		SC_THREAD (First_Thread);
		SC_THREAD (Second_Thread);
	}
};

#endif
