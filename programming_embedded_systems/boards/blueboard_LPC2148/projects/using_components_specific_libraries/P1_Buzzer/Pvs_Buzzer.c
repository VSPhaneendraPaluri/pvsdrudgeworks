/*******************************************************************************
 CLASS DEFINITION	:	Buzzer On Externel Interrupt 2
 Architecture		:	ARM7TDMI-S
 MCU				:	NXP's LPC2148
 Evaluation Kit		:	Blueboard from NGX Technologies
 Author				:	P V S Phaneendra
 Date of Creation	: 	02-Jan-2011
 LICENCE			:	Anyone is to use, copy, publish or modify this file as
 						long as this header isn't removed
********************************************************************************/

#include "Pvs_Buzzer.h"

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
void PvsConfigureBuzzer (void)
{
	PINSEL2		|=	(0 << 25);
	IO1DIR		|=	pvs_Buzzer_Pin;
}

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
void PvsBuzzerOnOff (unsigned char Off0_On1, unsigned int timeDelay)
{
	PvsConfigureBuzzer();

	if(Off0_On1)
	{
		IO1SET		|=	pvs_Buzzer_Pin;
		PvsSetTimeDelay (timeDelay);
	}
	else
	{
		IO1CLR		|=	pvs_Buzzer_Pin;
		PvsSetTimeDelay (timeDelay);
	}
}
