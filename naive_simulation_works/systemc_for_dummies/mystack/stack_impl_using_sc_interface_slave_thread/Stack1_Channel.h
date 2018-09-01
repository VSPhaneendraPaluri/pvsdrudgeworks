#ifndef STACK1_CHANNEL_H
#define STACK1_CHANNEL_H

#include <systemc.h>
#include "Stack1_Master.h"
#include "Stack1_Slave.h"

#define MAX_SIZE	10

class Stack1_Channel : public Stack1_Master_IF, public Stack1_Slave_IF
{
	public :
		Stack1_Channel();
		void Push(int &);
		int Pop(void);

	private:
		int TopOfStack;
		int array[MAX_SIZE];
};

#endif	// End of STACK1_CHANNEL_H
