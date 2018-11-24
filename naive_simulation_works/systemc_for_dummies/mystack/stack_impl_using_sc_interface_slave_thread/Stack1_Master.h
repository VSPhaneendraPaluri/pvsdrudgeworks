#ifndef STACK1_MASTER_H
#define STACK1_MASTER_H

#include <systemc.h>
#include "Stack1_Master_IF.h"

SC_MODULE(Stack1_Master)
{
	sc_in<int>		  In_Port;
	sc_port<Stack1_Master_IF> Master_Port;

	void Push_Data(void);

	SC_CTOR(Stack1_Master)
	{
		SC_METHOD(Push_Data);
			sensitive << In_Port;
	}
};

#endif	// End of STACK1_MASTER_H
