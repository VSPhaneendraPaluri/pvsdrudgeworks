#ifndef SYSTEMC_THREADS1_H
#define SYSTEMC_THREADS1_H

#include <systemc.h>

SC_MODULE (SystemC_Threads1)
{
	sc_event a_thread_event, b_thread_event, c_thread_event, d_thread_event;

	void A_Thread(void);
	void B_Thread(void);
	void C_Thread(void);
	void D_Thread(void);
	
	SC_CTOR (SystemC_Threads1)
	{
		SC_THREAD(A_Thread);
			sensitive << a_thread_event;
			cout << "Initialized Thread A" << endl;

		SC_THREAD(B_Thread);
			sensitive << b_thread_event;
			cout << "Initialized Thread B" << endl;

		SC_THREAD(C_Thread);
			sensitive << c_thread_event;
			cout << "Initialized Thread C" << endl;

		SC_THREAD(D_Thread);
			sensitive << d_thread_event;
			cout << "Initialized Thread D" << endl;
	}
};

#endif // End of SYSTEMC_THREADS1_H
