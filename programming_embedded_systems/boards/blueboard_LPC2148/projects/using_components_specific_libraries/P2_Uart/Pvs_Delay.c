/*******************************************************************************
 CLASS DEFINITION	:	Time Delay Loop
 Architecture		:	ARM7TDMI-S
 MCU				:	NXP's LPC2148
 Evaluation Kit		:	Blueboard from NGX Technologies
 Author				:	P V S Phaneendra
 Date of Creation	: 	02-Jan-2011
 LICENCE		:	Anyone is to use, copy, publish or modify this file as long
 					as this header isn't removed
********************************************************************************/

#include "Pvs_Delay.h"

/*******************************************************************************
 FUNCTION		:	Set up time delay
 Input Parameter(s)	:	Delay Time (in ms)
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
void PvsSetTimeDelay (unsigned int timeDelay)
{
	unsigned int i, j, k;
	
	// Set up desired delay (in ms)
	for(i = 0; i <timeDelay; i++)
	{
		for(j = 0; j < 1000; j++)
		{	
			// Sets up time delay loop for 10 us
			for(j = 0; k < 35; k++);
		}
	}
}

