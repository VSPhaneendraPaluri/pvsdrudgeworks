/*******************************************************************************
 CLASS HEADER	:	Buzzer On Externel Interrupt 2
 Architecture	:	ARM7TDMI-S
 MCU			:	NXP's LPC2148
 Evaluation Kit	:	Blueboard from NGX Technologies
 Author			:	P V S Phaneendra
 Email ID		:	pvs.myworks@gmail.com
 Date of Creation	: 	02-Jan-2011
 LICENCE		:	Anyone is to use, copy, publish or modify this file as long
 					as this header isn't removed
********************************************************************************/
	
#ifndef _PVS_BUZZER_H_
#define _PVS_BUZZER_H_

#include <lpc214x.h>
#include "Pvs_Delay.h"

#define pvs_Buzzer_Pin	(1 << 25)		// Buzzer on Port 1 Pin 25

/*******************************************************************************
 FUNCTION			:	Set up the Pin Select Block & Pin direction for Buzzer Output
 Input Parameter(s)	:	'1' if Externel Interrupt or '0' if normal (unsigned char)
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
void PvsConfigureBuzzer (void);

/*******************************************************************************
 FUNCTION			:	On & Off the Buzzer Pin
 Input Parameter(s)	:	BuzzerOnOff decision bit, Time Delay (in ms)
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
void PvsBuzzerOnOff (unsigned char, unsigned int);

#endif
