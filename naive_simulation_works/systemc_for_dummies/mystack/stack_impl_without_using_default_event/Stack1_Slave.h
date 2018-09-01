#ifndef STACK1_SLAVE_H
#define STACK1_SLAVE_H

#include <systemc.h>
#include "Stack1_Slave_IF.h"

SC_MODULE(Stack1_Slave)
{

	sc_port<Stack1_Slave_IF>	Slave_Port;
	sc_out<int>	  		Out_Port;

	void	Pop_Data(void);  	

	SC_CTOR(Stack1_Slave)
	{
		SC_METHOD(Pop_Data);
			sensitive << Slave_Port;
	}
};

#endif	// End of STACK1_SLAVE_H
