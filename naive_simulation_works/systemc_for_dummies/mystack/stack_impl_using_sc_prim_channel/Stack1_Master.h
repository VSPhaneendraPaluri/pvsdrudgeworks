#ifndef STACK1_MASTER_H
#define STACK1_MASTER_H

#include <systemc.h>
#include "Stack1_Master_IF.h"

#define MAX_DATA_LIMIT	15

SC_MODULE(Stack1_Master)
{
	sc_port<Stack1_Master_IF> Master_Port;

	int i, array[15];
	
	void Push_Data(void);

	SC_CTOR(Stack1_Master)
	{
		for(i = 0; i < MAX_DATA_LIMIT; i++)
			array[i] = i;		

		SC_THREAD(Push_Data);
	}
};

#endif	// End of STACK1_MASTER_H
