#include <LPC214x.H>
#include "P_V_S_Phaneendra.h"

#define	enableVectIRQBit 	(1 << 5)

#define	PS2_CLK		0x00010000	// Port 0 Pin 16
#define	PS2_DATA	0x00010000	// Port 1 Pin 16

void setDelay (double);
void configureSerialUart0 (double, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char);
void charTransmitFromUart0 (unsigned char);
//void initVICInterruptSource (unsigned char);
void pinSelectInterruptSource (unsigned char);
void regVICInterruptSelect (unsigned char, unsigned char);
void regVICInterruptEnable (unsigned char);
void EXT_IRQ14 (void) __irq;

int main(void)
{
	unsigned char interruptSourceType	= 	14;

	// _______________________ EXTERNAL INTERRUPT#0 (EINT0) - IRQ#14  ___________________________
   					
	// Selecting the Pin (Port0) A.16 for connecting to a pin functioning in External Interrupt Mode
	pinSelectInterruptSource(interruptSourceType);			//	Pin Select Function for EINT0
	PINSEL1	|=	(0 << 16);									//	Enabling Port 1 Pin 16 as a GPIO pin
  	IO1DIR	|=	(0 << 16);									//	Setting the above pin as input type

	// Setting the Registers
	EXTMODE	|=	(1 << 2);			// Level - Triggered = 0; Edge - Triggered = 1;
	EXTPOLAR |= (0 << 2);			// Falling Edge/ Low Level = 0; Rising Edge/ High Level = 1;
	
	// Argument#1: IRQ = 0/ FIQ = 1; Argument#2: VICInterruptSourceType
	//Writing all zeros classifying all interrupts as General Purpose IRQs
	regVICInterruptSelect(0,interruptSourceType);		

	// Writing to the Vector Controller register
	// Enables the Vector Interrupt Controller with assigned priority level (Highest = 0)
	VICVectCntl1	=	(enableVectIRQBit)|(interruptSourceType);		

	// Stores the vectored address of the C function when the interrupt occurs
	VICVectAddr1 	= 	(unsigned)EXT_IRQ14;   
	
	// Enables the ARM7 CPU for EINT1 class external interrupt
	regVICInterruptEnable (interruptSourceType);

	EXTINT	|=	(0 << 0);

	configureSerialUart0 (9600, 0, 0, 0, 1, 8);

	while(1);
}
/*
void EXT_IRQ14 (void) __irq
{
	static unsigned char var1				=	0;
	unsigned char clockCopy					=	PS2_CLK;
	static unsigned int elevenBitData		=	0;
	static unsigned char dataReceivedFromKeyboard	=	0;		

	while(var1	!=	11)
	{
		if((clockCopy	== 0)&(var1 == 0))
		{
			elevenBitData	|=	(PS2_DATA << var1);			
		}
		else if ((clockCopy == 0)&((var1 >= 1)&&(var1 <= 8)))
		{
			dataReceivedFromKeyboard	|=	(PS2_DATA	<<	var1);
			elevenBitData	|=	(PS2_DATA << var1);
		}
		else if((clockCopy == 0)&(var1 == 9))
		{
			elevenBitData	|=	(PS2_DATA << var1);
		}
		else if((clockCopy == 0)&(var1 == 10))
		{
			elevenBitData	|=	(PS2_DATA << var1);
		}
		var1++;
	}
	checkWord (elevenBitData);
	charTransmitFromUart0 (dataReceivedFromKeyboard);

	EXTINT	|=	(1 << 0);
	VICVectAddr	=	0;
}*/

void EXT_IRQ14 (void) __irq
{
	static volatile unsigned char var1 				=	0;
	unsigned volatile char clockStatusSignal		=	(IO1PIN & PS2_CLK);
	unsigned volatile char dataStatusSignal			=	(IO1PIN & PS2_DATA);
	static unsigned int elevenBitData				=	0;		

	while(!clockStatusSignal)						// When PSK_CLK line is sensed low
	{
		elevenBitData	|=	(dataStatusSignal << var1);
		var1++;
	}
	checkWord (elevenBitData);

	EXTINT	|=	(1 << 0);
	VICVectAddr	=	0;
}