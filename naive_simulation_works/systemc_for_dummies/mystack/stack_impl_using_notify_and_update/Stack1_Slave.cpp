#include "Stack1_Slave.h"

void Stack1_Slave::Pop_Data(void)
{
	int readData;

	readData = Slave_Port->Pop();
	cout << "\nSlave reading the data : " << readData << "\tat : " << sc_time_stamp() << endl;
	Out_Port.write(readData);
}
