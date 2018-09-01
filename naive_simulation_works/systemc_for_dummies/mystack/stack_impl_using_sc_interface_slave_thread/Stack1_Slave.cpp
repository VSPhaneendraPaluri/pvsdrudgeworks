#include "Stack1_Slave.h"

void Stack1_Slave::Pop_Data(void)
{
	int readData;

	while(1)
	{
		readData = Slave_Port->Pop();
		Out_Port.write(readData);
		wait(5.0, SC_NS);
	}
}
