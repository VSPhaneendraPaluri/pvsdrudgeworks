#ifndef STACK1_CHANNEL_H
#define STACK1_CHANNEL_H

#include <systemc.h>
#include "Stack1_Master_IF.h"
#include "Stack1_Slave_IF.h"

#define MAX_SIZE	10

class Stack1_Channel : public Stack1_Master_IF, public Stack1_Slave_IF, public sc_prim_channel
{
	public :
		Stack1_Channel();
	
		void Push(int &);
		int Pop(void);

		void update();

	private:
		int TopOfStack;
		int array[MAX_SIZE];
		int tempValue;
		int tempIndex;
};

#endif	// End of STACK1_CHANNEL_H
