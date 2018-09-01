#include "Stack1_Master.h"

void Stack1_Master::Push_Data(void)
{
	static int index = 0;
	
	while(1)
	{
		if(index == (MAX_DATA_LIMIT - 1))
			cout << "\nFinished transmitting all data within the array." << endl;
		
		Master_Port->Push(array[index++]);
		cout << "\nData Pushed by Master................." << index << "\t@ " << sc_time_stamp() << endl;
		wait(2.0, SC_NS);
	}
}
