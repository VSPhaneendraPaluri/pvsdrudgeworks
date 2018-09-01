#ifndef STACK1_MASTER_IF_H
#define STACK1_MASTER_IF_H

#include <systemc.h>

class Stack1_Master_IF : virtual public sc_interface
{
	public	:
		virtual void Push(int &) = 0;
		virtual const sc_event & My_Event_Notifier() const = 0;
};

#endif	// End of STACK1_MASTER_IF_H
