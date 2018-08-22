#include <LPC214x.H>
#include "P_V_S_Phaneendra.h" 

void configureSerialUart0 (double, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char);
void charTransmitFromUart0 (unsigned char);
unsigned char charReceiveAtUart0 (void);

struct TimeStamp {
   unsigned char Sec;
   unsigned char Min;
   unsigned char Hours;
   unsigned char DaysOfWeek;
};

int main (void)
{
	unsigned char readByte;	

	configureSerialUart0 (9600, 0, 0, 0, 1, 3);
	
	ILR	=	0x3;	
	ILR = 	0x0;
	CCR	=	0x1;
	CIIR =	0x1;
	AMR = 0xFE;	

	DOW	=	(unsigned int)2;	
	DOM	=	(unsigned int)(20);
	MONTH	=	11;
	YEAR	=	2010;
	HOUR	=	14;
	MIN		=	30;
	SEC		=	30;

	PREINT	=	366;
	PREFRAC	=	6912;

	while(1)
	{
		for(readByte = 0; readByte <= 127; readByte++)
			charTransmitFromUart0 (readByte);
		readByte = charReceiveAtUart0 ();
		charTransmitFromUart0 (readByte);
		//readByte = charReceiveAtUart0();
		//charTransmitFromUart0(readByte);

		//readByte    =	CTIME0 >> 24;
		//charTransmitFromUart0(readByte);
		
		//readByte	=	ILR;
		//charTransmitFromUart0(readByte);		
	}
}



