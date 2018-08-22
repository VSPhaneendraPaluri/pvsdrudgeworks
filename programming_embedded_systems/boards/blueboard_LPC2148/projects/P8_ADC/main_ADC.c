#include "P_V_S_Phaneendra.h"

int main (void)
{			
	unsigned char rb;
	unsigned int i;
	  
	configureSerialUart0 (9600, 0, 0, 0, 1, 8);
	rb	=	charReceiveAtUart0 ();
	charTransmitFromUart0 (rb);

	// Set-up the PINSEL block for ADC Operation
	PINSEL1	|=	0x01000000;
	
	//	Set ADC Input Channel:	4th channel =	AD0Cr[7:0]	=	0x08	=	(1 << 3)
	//  Clock Divisor value (4.5MHz Max): AD0CR[15:8] = VPBDIV/(CLKDIV + 1)= 4.5MHz => CLKDIV = 3 = 0x03 	 
	//	AD0CR[16] = BurstMode = 0 (Software controlled conversion)
	//	No. of Clock Pulses & Resolution:  AD0CR[19:17]	=  CLKS = "000" (11 clocks & 10 bits) - Software controlled
	//  ADC Operational: AD0CR[21] = PDN (value = 1) = 1
	//	Pins 20, Pins [23:22] & Pin[31:28] shouldn't be written ones
	//  AD0CR[26:24] = "000" & AD0CR[27] = 0
	AD0CR	=	0x00200308;

	AD0CR	|=	0x01000000;	// Start conversion now

	while(1)
	{
		do
		{
			i	=	AD0DR3;				// Here, MSB of AD0DR3 is set high.    
		}
		while((i & 0x80000000) == 0);  	// After reading MSB of AD0DR3 becomes low automatically
		charTransmitFromUart0 ((i >> 6) & 0x3FF);		// Read the 10-bit value to the UART0
	}
}
