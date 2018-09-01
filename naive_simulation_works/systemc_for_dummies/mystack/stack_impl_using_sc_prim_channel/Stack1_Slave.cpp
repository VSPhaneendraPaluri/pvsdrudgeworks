#include "Stack1_Slave.h"

void Stack1_Slave::Pop_Data(void)
{
	int readData;
	
	while(1)
	{
		readData = Slave_Port->Pop();
		cout << "\nSlave reading the data from channel: " << readData << "\tat : " << sc_time_stamp() << endl;
		wait(2.0, SC_NS);
	}
}
