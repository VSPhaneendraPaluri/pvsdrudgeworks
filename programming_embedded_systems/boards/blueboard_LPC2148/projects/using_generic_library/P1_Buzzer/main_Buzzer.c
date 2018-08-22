#include "P_V_S_Phaneendra.h"

void buzzer(unsigned char, unsigned long int);

int main(void)
{
	while(1)
	{
		buzzer(0,1000000);			// Argument#1 indicates Buzzer ON/OFF = 1/0; Argument#2 indicates Delay_Time
		buzzer(1,1000000);
	}
}


