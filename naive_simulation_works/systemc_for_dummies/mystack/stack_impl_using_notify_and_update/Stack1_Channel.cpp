#include "Stack1_Channel.h"

Stack1_Channel::Stack1_Channel(sc_module_name name)
	:sc_module(name)
{
	TopOfStack = -1;
	push_status = false;
	//cout << "\nChannel hierarchy is : " << sc_module::kind()  ;
}

const sc_event & Stack1_Channel::default_event() const
{
	cout << "\nInstatiating 'MyEvent' ............." << endl;
	return(My_Event);
}

void Stack1_Channel::update()
{
	push_status = false;
	My_Event.notify(5.0, SC_NS);
}

void Stack1_Channel::Push(int & input)
{
	if(!push_status)	
	{
		if(TopOfStack < MAX_SIZE)
        	{
			array[++TopOfStack] = input;
			request_update();
			push_status = true;
			cout << "\nInteger value received from Master_IF : " << array[TopOfStack] << endl;
		}
		else if(TopOfStack == MAX_SIZE)
			cout << "\nStack Is Full.  You cannot push more elements." << endl;	
	}
}

int Stack1_Channel::Pop(void) 
{
	int returnValue;
	
	cout << "\nPop Event notified by Channel to slave at : " << sc_time_stamp() << endl;

	if(TopOfStack < 0)
		cout << "\nStack is empty.  You cannot pop anymore elements." << endl;
	else 
	{	
		returnValue = array[TopOfStack--]; 
		cout << "\nInterger value transmitted to Slave_IF : " << returnValue << endl;	
		return(returnValue);
	}
}

