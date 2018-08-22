/*******************************************************************************
 CLASS DEFINITION	:	VECTORED INTERRUPT CONTROLLER MASKS
 Architecture		:	ARM7TDMI-S
 MCU				:	NXP's LPC2148
 Evaluation Kit		:	Blueboard from NGX Technologies
 Author				:	P V S Phaneendra
 Email ID			:	pvs.myworks@gmail.com
 Date of Creation	: 	11-Jan-2011
 LICENCE			:	Anyone is to use, copy, publish or modify this file as
 						long as this header isn't removed
********************************************************************************/
	
#include "Pvs_Interrupt_Mask.h"

unsigned char VICMask;

/*******************************************************************************
 FUNCTION			:	Selection of the VIC Interrupt Channel
 Input Parameter(s)	:	VIC Channel Number (See the above table)
 Output Parameter(s):	Not Applicable
 Architecture		:	ARM7TDMI-S
 MCU				:	NXP's LPC2148
 Evaluation Kit		:	Blueboard from NGX Technologies
 Author				:	P V S Phaneendra
 Email ID			:	pvs.myworks@gmail.com
 Date of Creation	: 	11-Jan-2011
 LICENCE			:	Anyone is to use, copy, publish or modify this file as
 						long as this header isn't removed
********************************************************************************/
void PvsSelectVicChannel (unsigned char interruptChannel)
{
	VICMask	=	interruptChannel;	
}

/*******************************************************************************
 FUNCTION			:	Setting of the Interrupt Mode on Externel Interrupt Pin
 Input Parameter(s)	:	'0' if Level-Triggered or '1' if Edge-Triggered (unsigned char)
 Output Parameter(s):	Not Applicable
 Architecture		:	ARM7TDMI-S
 MCU				:	NXP's LPC2148
 Evaluation Kit		:	Blueboard from NGX Technologies
 Author				:	P V S Phaneendra
 Email ID			:	pvs.myworks@gmail.com
 Date of Creation	: 	11-Jan-2011
 LICENCE			:	Anyone is to use, copy, publish or modify this file as
 						long as this header isn't removed
********************************************************************************/
void PvsSelectExtIntMode (unsigned char extIntMode)
{
	if((VICMask - 14) == 2)
	{
		PINSEL0	|=	(PINSEL0 & ~((unsigned)3 << 30))|((unsigned)2 << 30);
		#ifdef _PVS_UART_H_
		PvsTransmitFromUart0(PINSEL0 >> 24);
		#endif
	}
	
	EXTMODE	|=	(extIntMode << (VICMask - 14));
	#ifdef _PVS_UART_H_
	PvsTransmitFromUart0(EXTMODE);
	#endif
}

/*******************************************************************************
 FUNCTION			:	Setting of the Interrupt Mode on Externel Interrupt Pin
 Input Parameter(s)	:	'0' if Low-Level or Falling Edge (High-to-Low) or
 						'1' if High-Level or Rising Edge (Low-to-High) (unsigned char)
 Output Parameter(s):	Not Applicable
 Architecture		:	ARM7TDMI-S
 MCU				:	NXP's LPC2148
 Evaluation Kit		:	Blueboard from NGX Technologies
 Author				:	P V S Phaneendra
 Email ID			:	pvs.myworks@gmail.com
 Date of Creation	: 	11-Jan-2011
 LICENCE			:	Anyone is to use, copy, publish or modify this file as
 						long as this header isn't removed
********************************************************************************/
void PvsSelectExtIntPolarity (unsigned char extIntPolarity)
{
	EXTPOLAR	|=	(extIntPolarity << (VICMask - 14));
	#ifdef _PVS_UART_H_
	PvsTransmitFromUart0(EXTPOLAR);
	#endif
}

/*******************************************************************************
 FUNCTION			:	Set/Clear External Interrupt Register
 Input Parameter(s)	:	'0' if to disable or '1' if to enable successive interrupt
 						detection (unsigned char)
 Output Parameter(s):	Not Applicable
 Architecture		:	ARM7TDMI-S
 MCU				:	NXP's LPC2148
 Evaluation Kit		:	Blueboard from NGX Technologies
 Author				:	P V S Phaneendra
 Email ID			:	pvs.myworks@gmail.com
 Date of Creation	: 	11-Jan-2011
 LICENCE			:	Anyone is to use, copy, publish or modify this file as
 						long as this header isn't removed
********************************************************************************/
void PvsSelectExtInt (unsigned char extIntSetClr)
{
	EXTINT	|=	(extIntSetClr << (VICMask - 14));
	#ifdef _PVS_UART_H_
	PvsTransmitFromUart0(EXTINT);
	#endif
}

/*******************************************************************************
 FUNCTION			:	Set the value for VIC Interrupt Register
 Input Parameter(s)	:	'0' if IRQ and '1' if FIQ (unsigned char)
 Output Parameter(s):	Not Applicable
 Description		:	Writing '0' doesn't clear or disable the interrupt.  It
 						makes a vectored interrupt a non-vectored interrupt
 Architecture		:	ARM7TDMI-S
 MCU				:	NXP's LPC2148
 Evaluation Kit		:	Blueboard from NGX Technologies
 Author				:	P V S Phaneendra
 Email ID			:	pvs.myworks@gmail.com
 Date of Creation	: 	11-Jan-2011
 LICENCE			:	Anyone is to use, copy, publish or modify this file as
 						long as this header isn't removed
********************************************************************************/
void PvsSetVicIrqFiq (unsigned char IRQ0_FIQ1)
{
	VICIntSelect	|=	(IRQ0_FIQ1 << pvs_VIC_Channel(VICMask));
	#ifdef _PVS_UART_H_
	PvsTransmitFromUart0(VICIntSelect >> 16);
	#endif
}

/*******************************************************************
********************** VIC Masks Table *****************************
*	WatchDog Interrupt			VIC_Mask = 	0
*   Software Interrupt			VIC_Mask =	1
*	EmbeddedICE_DebugCommRx		VIC_Mask =	2
*	EmbeddedICE_DebugCommTx		VIC_Mask =	3
* 	TIMER0						VIC_Mask =	4
* 	TIMER1						VIC_Mask =	5
* 	UART0						VIC_Mask =	6
* 	UART1						VIC_Mask =	7
*	PWM0						VIC_Mask =	8
* 	I2C0						VIC_Mask =	9
*	SPI0						VIC_Mask =	10
*	SP1 (SSP)					VIC_Mask =	11
*	PLL							VIC_Mask =	12
*	RTC							VIC_Mask =	13
*	EINT0						VIC_Mask =	14
*	EINT1						VIC_Mask =	15
*	EINT2						VIC_Mask =	16
*	EINT3						VIC_Mask =	17
*	ADC0						VIC_Mask =	18
*	I2C1						VIC_Mask =	19
*	BOD							VIC_Mask =	20
*	ADC1						VIC_Mask =	21
*	USB							VIC_Mask =	22
*********************************************************************/

/*******************************************************************************
 FUNCTION			:	Set the value for VIC Vectored Control Register	and
 						VIC Vectored Address Register
 Input Parameter(s)	:	Priority Level (unsigned char)
 Output Parameter(s):	Not Applicable
 Description		:	Choose between '0' and '15'.  This assigns the desired 
 						priority to the peripheral (Highest = '0' & Lowest = '15').
						Also sets the enable bit high for interrupt to occur.
						This function contains the address of the 'C' function
 						(specify 'unsigned' if it lies within the same segment or
						'unsigned long' if in the far segment.  Likewise, 
						'unsigned int'.  Specify '__irq' at the end of the function
						name indicating to the compiler that this is an IRQ routine
 Architecture		:	ARM7TDMI-S
 MCU				:	NXP's LPC2148
 Evaluation Kit		:	Blueboard from NGX Technologies
 Author				:	P V S Phaneendra
 Email ID			:	pvs.myworks@gmail.com
 Date of Creation	: 	11-Jan-2011
 LICENCE			:	Anyone is to use, copy, publish or modify this file as
 						long as this header isn't removed
********************************************************************************/
void PvsSetVicVectCntlAddr (unsigned char Priority)
{
	switch(Priority)
	{
		case 0	:	
				{	
					VICVectCntl0	= (pvs_VIC_Enable)|(VICMask); 
					break;
				}
		case 1	:	
				{	
					VICVectCntl1 	= (pvs_VIC_Enable)|(VICMask); 
					break;
				}
		case 2	:
				{
					VICVectCntl2 	= (pvs_VIC_Enable)|(VICMask); 
					break;
				}
		case 3	:
				{
					VICVectCntl3 	= (pvs_VIC_Enable)|(VICMask); 
					break;
				}
		case 4	:
				{
					VICVectCntl4 	= (pvs_VIC_Enable)|(VICMask); 
					break;
				}
		case 5	:
				{
					VICVectCntl5 	= (pvs_VIC_Enable)|(VICMask);
					#ifdef _PVS_UART_H_
					PvsTransmitFromUart0(VICVectCntl5 >> 16); 
					#endif
					VICVectAddr5	= (unsigned)PvsPriority5;
					break;
				}
		case 6	:
				{
					VICVectCntl6 	= (pvs_VIC_Enable)|(VICMask); 
					break;
				}
		case 7	:
				{
					VICVectCntl7 	= (pvs_VIC_Enable)|(VICMask); 
					break;
				}
		case 8	:
				{	
					VICVectCntl8 	= (pvs_VIC_Enable)|(VICMask); 
					break;
				}
		case 9	:
				{	
					VICVectCntl9 	= (pvs_VIC_Enable)|(VICMask); 
					break;
				}
		case 10	:
				{
					VICVectCntl10 	= (pvs_VIC_Enable)|(VICMask); 
					break;
				}
		case 11	:
				{
					VICVectCntl11 	= (pvs_VIC_Enable)|(VICMask); 
					break;
				}
		case 12	:
				{
					VICVectCntl12 	= (pvs_VIC_Enable)|(VICMask); 
					break;
				}
		case 13	:
				{
					VICVectCntl13 	= (pvs_VIC_Enable)|(VICMask); 
					break;
				}
		case 14	:
				{
					VICVectCntl14 	= (pvs_VIC_Enable)|(VICMask); 
					break;
				}
		case 15	:
				{
					VICVectCntl15 	= (pvs_VIC_Enable)|(VICMask); 
					break;
				}
		default	:	break;
	}
}

/*******************************************************************************
 FUNCTION			:	Enables the Vector Interrupt
 Input Parameter(s)	:	Vectored Interrupt Channel
 Output Parameter(s):	Not Applicable
 Description		:	
 Architecture		:	ARM7TDMI-S
 MCU				:	NXP's LPC2148
 Evaluation Kit		:	Blueboard from NGX Technologies
 Author				:	P V S Phaneendra
 Email ID			:	pvs.myworks@gmail.com
 Date of Creation	: 	11-Jan-2011
 LICENCE			:	Anyone is to use, copy, publish or modify this file as
 						long as this header isn't removed
********************************************************************************/
void PvsSetVicVectEnable (unsigned char Enable)
{
	VICIntEnable	|=	(Enable << pvs_VIC_Channel(VICMask));
	#ifdef _PVS_UART_H_
	PvsTransmitFromUart0(VICIntEnable >> 16);
	#endif
}


void PvsPriority5 (void) __irq
{
	#ifdef _PVS_BUZZER_H_
	PvsBuzzerOnOff (1, 1000);
	PvsBuzzerOnOff (0, 1000);
	#endif	

	EXTINT	|=	(1 << 2);
	//PvsSelectExtInt(1);  
	VICVectAddr	= 0x00000000;
}
