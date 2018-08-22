/*******************************************************************************
 PROJECT			:	Buzzer On Externel Interrupt 2
 Architecture		:	ARM7TDMI-S
 MCU				:	NXP's LPC2148
 Evaluation Kit		:	Blueboard from NGX Technologies
 Author				:	P V S Phaneendra
 Email ID			:	pvs.myworks@gmail.com
 Date of Creation	: 	02-Jan-2011
 LICENCE			:	Anyone is to use, copy, publish or modify this file as
 						long as this header isn't removed
********************************************************************************/							 
							 
#include "Pvs_Delay.h"
#include "Pvs_Buzzer.h"
#include "Pvs_Interrupt_Mask.h"
#include "Pvs_Uart.h"

int main (void)
{
	unsigned char data;
	/*EXTMODE		=	(0 << 2);		//	Level Triggered / Edge Triggered = 0/1
	EXTPOLAR	=	(0 << 2);		//	Low Level/ Falling Edge = 0; High Level/ Rising Edge = 1;
	
	VICIntSelect	=	(0 << 16);
	VICVectCntl0	=	(1 << 5)|(16);
	VICVectAddr0	=	(unsigned)PvsPriority5;
	VICIntEnable	=	(1 << 16);
	
	EXTINT	|=	(0 << 2);*/

	/*PvsSelectVicChannel(16);
	PvsSelectExtIntMode(0);
	PvsSelectExtIntPolarity(1);
	PvsSetVicIrqFiq(0);
	PvsSetVicVectCntlAddr(5);
	PvsSetVicVectEnable(1);
	PvsSelectExtInt(0);

	PvsSelectVicChannel(6);
	PvsSetVicIrqFiq(0);
	PvsSetVicVectCntlAddr(4);
	PvsSetVicVectEnable(1);
	PvsSelectExtInt(0);*/

	PvsConfigureUart0(9600, 0, 0, 0, 1, 8);

	while(1);
}
