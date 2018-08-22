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

#ifndef _PVS_UART_H_
#define _PVS_UART_H_

#include <lpc214x.h>

#define pvs_Uart0_Tx  (1 << 0)
#define pvs_Uart0_Rx  (1 << 2)

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
void PvsSelectUart0 (void);

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
void PvsConfigureUart0 (unsigned int, unsigned char, unsigned char, unsigned char, \
						unsigned char, unsigned char);

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
unsigned char PvsReceiveAtUart0 (void);

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
void PvsTransmitFromUart0 (unsigned char);

#endif
