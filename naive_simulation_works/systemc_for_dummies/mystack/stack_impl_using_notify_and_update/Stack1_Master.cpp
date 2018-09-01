#include "Stack1_Master.h"

void Stack1_Master::Push_Data(void)
{
	int writeData;
	
	writeData = In_Port.read();
	Master_Port->Push(writeData);
}
