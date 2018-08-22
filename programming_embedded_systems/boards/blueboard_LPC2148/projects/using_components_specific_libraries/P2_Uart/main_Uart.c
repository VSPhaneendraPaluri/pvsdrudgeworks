/*******************************************************************************
 PROJECT		:	UART0 Communication
 Architecture	:	ARM7TDMI-S
 MCU			:	NXP's LPC2148
 Evaluation Kit	:	Blueboard from NGX Technologies
 Author			:	P V S Phaneendra
 Email ID		:	pvs.myworks@gmail.com
 Date of Creation	: 	02-Jan-2011
 LICENCE		:	Anyone is to use, copy, publish or modify this file as long
 					as this header isn't removed
********************************************************************************/
#include "Pvs_Uart.h"
#include "Pvs_Delay.h"
#include "Pvs_Buzzer.h"

void PvsExternalBuzzer (void) __irq;

int main (void)
{
	unsigned char data;
	unsigned char setbreak = 0;
	unsigned char parity = 0;
	unsigned char N = 0;
	unsigned char stopbits = 1;
	unsigned char wordlen = 8;
	double baudrate = 9600;

	VPBDIV	=	0x00;
	PvsConfigureUart0 (baudrate, setbreak, parity, N, stopbits, wordlen);

	EXTMODE	|= (0 << 2);	   // Level Triggered = 0; Edge-Triggered = 1;
	EXTPOLAR	|= (1 << 2);   // Low/High = 0/1; FallingEdge/RisingEdge = 0/1;

	/* To Invoke the buzzer on EINT2 Select using Vectored Interrupts*/
	PINSEL0	|=	(PINSEL0 & ~((unsigned)3 << 30))|((unsigned)1 << 31);

	VICIntSelect	|=	(0 << 16);  // IRQ on EINT2
	//EXTINT	|=	(1 << 2);
	VICVectAddr0	=	(unsigned)PvsExternalBuzzer;
	VICVectCntl0	|=	(1 << 5)|(16);
	VICIntEnable	|=	(1 << 16);

	while(1)
	{
		for(data = 0; data <= 127; data++)
			PvsTransmitFromUart0 (data);
		data	=	PvsReceiveAtUart0 ();
		PvsTransmitFromUart0(data);
	} 
}

void PvsExternalBuzzer (void) __irq
{
	PvsBuzzerOnOff (1, 1000);
	PvsBuzzerOnOff (0, 1000);
	
	EXTINT	|=	(1 << 2);
	VICVectAddr	=	0x00000000;	
}
