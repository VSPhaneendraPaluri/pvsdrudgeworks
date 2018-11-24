#include "Stack1_Channel.h"

Stack1_Channel::Stack1_Channel()
{
	TopOfStack = -1;
	
}

void Stack1_Channel::Push(int & input)
{
	if(TopOfStack < MAX_SIZE)
        {
		array[++TopOfStack] = input;
		cout << "\nInteger value received from Master_IF : " << array[TopOfStack] << endl;
	}
	else if(TopOfStack == MAX_SIZE)
		cout << "\nStack Is Full.  You cannot push more elements." << endl;	
}

int Stack1_Channel::Pop(void) 
{
	int returnValue;

	if(TopOfStack < 0)
		cout << "\nStack is empty.  You cannot pop anymore elements." << endl;
	else 
	{	
		returnValue = array[TopOfStack--]; 
		cout << "\nInterger value transmitted to Slave_IF : " << returnValue <<"at time stamp :"<<sc_time_stamp()<< endl;	
		return(returnValue);
	}
}

