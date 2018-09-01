#ifndef STACK1_CHANNEL_H
#define STACK1_CHANNEL_H

#include <systemc.h>
#include "Stack1_Master.h"
#include "Stack1_Slave.h"

#define MAX_SIZE	10

class Stack1_Channel : public Stack1_Master_IF, public Stack1_Slave_IF, public sc_prim_channel, public sc_module
{
	public :
		SC_HAS_PROCESS(Stack1_Channel);
		Stack1_Channel(sc_module_name name);
		const sc_event & default_event() const;	
	
		void Push(int &);
		int Pop(void);

		void update();

	private:
		sc_event	My_Event;
		bool		push_status;
		int TopOfStack;
		int array[MAX_SIZE];
             
};

#endif	// End of STACK1_CHANNEL_H
