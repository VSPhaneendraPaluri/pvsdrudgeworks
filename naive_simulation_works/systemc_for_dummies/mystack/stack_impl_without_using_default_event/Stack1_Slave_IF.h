#ifndef STACK1_SLAVE_IF_H
#define STACK1_SLAVE_IF_H

#include <systemc.h>

class Stack1_Slave_IF : virtual public sc_interface
{
	public	:
		virtual int Pop(void) = 0;
		virtual const sc_event & My_Event_Notifier() const = 0;
};

#endif	// End of STACK1_SLAVE_IF_H
