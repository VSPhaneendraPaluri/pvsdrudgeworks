#include "Stack1_Slave.h"

void Stack1_Slave::Pop_Data(void)
{
	int readData;

	readData = Slave_Port->Pop();
	Out_Port.write(readData);
}
