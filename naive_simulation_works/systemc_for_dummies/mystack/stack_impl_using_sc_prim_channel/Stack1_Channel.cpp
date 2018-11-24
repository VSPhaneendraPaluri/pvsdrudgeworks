#include "Stack1_Channel.h"

Stack1_Channel::Stack1_Channel()
{
	TopOfStack = -1;
	tempValue = 0;
	tempIndex = 0;
}

void Stack1_Channel::update()
{
	array[++TopOfStack] = tempValue;
	tempIndex = TopOfStack;
}

void Stack1_Channel::Push(int & input)
{
	if(TopOfStack < MAX_SIZE)
       	{
		tempValue = input;
		request_update();
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
		returnValue = array[tempIndex]; 
		return(returnValue);
		tempValue--;
	}
}

