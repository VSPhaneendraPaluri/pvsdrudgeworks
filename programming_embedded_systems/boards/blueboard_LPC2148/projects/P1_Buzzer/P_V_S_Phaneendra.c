#include <LPC214x.h>

void buzzer(unsigned char, unsigned long int);
void delay(unsigned long int);

// -------------------------- BUZZER ----------------------------
void buzzer(unsigned char ON1_OFF0, unsigned long int timedelay)
{
	IO1DIR	= 	0x02000000;
	if(ON1_OFF0)
	{
		IO1SET 	=	0x02000000;
		delay(timedelay);
	}
	else
	{
		IO1CLR	=	0x02000000;	
		delay(timedelay);
	}
}

// ------------------------ DELAY FUNCTION ----------------------
void delay(unsigned long int looptime)
{
	unsigned long int i;
	for(i = 0; i <= looptime; i++);
}
