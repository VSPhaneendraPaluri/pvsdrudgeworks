/*******************************************************************************
 CLASS DEFINITION	:	Buzzer On Externel Interrupt 2
 Architecture		:	ARM7TDMI-S
 MCU				:	NXP's LPC2148
 Evaluation Kit		:	Blueboard from NGX Technologies
 Author				:	P V S Phaneendra
 Email ID			:	pvs.myworks@gmail.com
 Date of Creation	: 	02-Jan-2011
 LICENCE			:	Anyone is to use, copy, publish or modify this file as
 						long as this header isn't removed
********************************************************************************/

#include "Pvs_Uart.h"

/*******************************************************************************
 FUNCTION			:	Select the pins for UART0 communication
 Input Parameter(s)	:	Not Applicable
 Output Parameter(s):	Not Applicable
 Architecture		:	ARM7TDMI-S
 MCU				:	NXP's LPC2148
 Evaluation Kit		:	Blueboard from NGX Technologies
 Author				:	P V S Phaneendra
 Email ID			:	pvs.myworks@gmail.com
 Date of Creation	: 	02-Jan-2011
 LICENCE			:	Anyone is to use, copy, publish or modify this file as
 						long as this header isn't removed
********************************************************************************/
void PvsSelectUart0 (void)
{
	PINSEL0	|=	(PINSEL0 & ~(3 << 0))|(pvs_Uart0_Tx);
	PINSEL0	|=	(PINSEL0 & ~(3 << 2))|(pvs_Uart0_Rx);	
}

/*******************************************************************************
 FUNCTION			:	Configure the Uart0
 Input Parameter(s)	:	BaudRate, BreakControl, ParitySelect, ParityEnable,
 						StopBits, DataBits 
 Output Parameter(s):	Not Applicable
 Architecture		:	ARM7TDMI-S
 MCU				:	NXP's LPC2148
 Evaluation Kit		:	Blueboard from NGX Technologies
 Author				:	P V S Phaneendra
 Email ID			:	pvs.myworks@gmail.com
 Date of Creation	: 	02-Jan-2011
 LICENCE			:	Anyone is to use, copy, publish or modify this file as
 						long as this header isn't removed
********************************************************************************/
void PvsConfigureUart0 (unsigned int baudrate, unsigned char breakControl, unsigned char paritySelect, \
						unsigned char parityEnable, unsigned char stopBitSelect, unsigned char wordLengthSelect)
{
	PvsSelectUart0();
	
	// Registers setting for customized baudrate of 'x' bauds/sec
	U0LCR = 0x80;		   // Set DLAB = 1 for configuring U0DLM:U0DLL

	if (baudrate == 1200)	
	{ 
		U0DLM = 0x03; 
		U0DLL = 0x0D; 
	}
	else if (baudrate == 2400)	
	{
		U0DLM = 0x01; 
		U0DLL = 0x86; 
	}
	else if (baudrate == 4800)	
	{
		U0DLM = 0x00; 
		U0DLL = 195;  
	}
	else if (baudrate == 9600)	
	{ 
		U0DLM = 0x00; 
		U0DLL = 97;   
	}
	else if (baudrate == 19200)	
	{
		U0DLM = 0x00; 
		U0DLL = 48;   
	}
	else if (baudrate == 38400)	
	{
		U0DLM = 0x00; 
		U0DLL = 24;   
	}
	else if (baudrate == 57600)	
	{
		U0DLM = 0x00; 
		U0DLL = 16;   
	}
	else if (baudrate == 115200)
	{
		U0DLM = 0x00; 
		U0DLL = 8;    
	}
	else if (baudrate == 230400)	
	{
		U0DLM = 0x00; 
		U0DLL = 4;    
	}

	U0FCR = 0x07;		   
	
	// Clear the DLAB bit and assign the configuration parameters to U0LCR
	U0LCR = (0 << 7)|(breakControl << 6)|(paritySelect << 4)|(parityEnable << 3)|	\
			((stopBitSelect - 1) << 2)|((wordLengthSelect - 5) << 0);
}

/*******************************************************************************
 FUNCTION			:	Receive At the Uart0
 Input Parameter(s)	:	Not Applicable
 Output Parameter(s):	Received Byte
 Architecture		:	ARM7TDMI-S
 MCU				:	NXP's LPC2148
 Evaluation Kit		:	Blueboard from NGX Technologies
 Author				:	P V S Phaneendra
 Email ID			:	pvs.myworks@gmail.com
 Date of Creation	: 	02-Jan-2011
 LICENCE			:	Anyone is to use, copy, publish or modify this file as
 						long as this header isn't removed
********************************************************************************/
unsigned char PvsReceiveAtUart0 (void)
{
	while(!(U0LSR & 0x20));
	return (U0RBR);
}

/*******************************************************************************
 FUNCTION		:	Transmit From the Uart0
 Input Parameter(s)	:	Byte To Transmit
 Output Parameter(s):	Not Applicable
 Architecture	:	ARM7TDMI-S
 MCU			:	NXP's LPC2148
 Evaluation Kit	:	Blueboard from NGX Technologies
 Author			:	P V S Phaneendra
 Email ID		:	pvs.myworks@gmail.com
 Date of Creation	: 	02-Jan-2011
 LICENCE		:	Anyone is to use, copy, publish or modify this file as long
 					as this header isn't removed
********************************************************************************/
void PvsTransmitFromUart0 (unsigned char TxByte)
{
	while(!(U0LSR & 0x20));
	U0THR	=	TxByte;
}

