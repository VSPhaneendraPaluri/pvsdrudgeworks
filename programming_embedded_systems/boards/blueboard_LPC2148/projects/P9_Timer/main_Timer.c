#include <LPC214x.H>
#include "P_V_S_Phaneendra.h"

int main (void)
{
 	unsigned char rb;
	
	configureSerialUart0 (115200, 0, 0, 0, 1, 8);
	rb	=	charReceiveAtUart0 ();
	charTransmitFromUart0 (rb);
	
	T0IR	=	0x00000001;	// 	Enable interrupt for Match Register 0
	T0TC	=	0x00000000;	//	Set Timer Counter to 0
	T0PR	=	0x00000010;	//	Set Prescaler to 1000
	T0PC	=	0x000003E8;	//	Prescaler value for Prescale Counter

	T0CTCR	=	0x00000000;	//	Timer Mode :  Increments TC on every POSITIVE EDGE of PCLK

	T0MCR	=	0x00000003;	//  Generate interrupt, reset TC and restart TC when (MPx) = (TC)

	T0MR0	=	0x0A0A;
	T0TCR	=	0x00000001;	//	Enable TCR[0]

	while(1)
		charTransmitFromUart0 (T0TC);
}
