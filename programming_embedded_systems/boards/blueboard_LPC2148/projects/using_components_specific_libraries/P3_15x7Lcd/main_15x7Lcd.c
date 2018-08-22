/*******************************************************************************
 PROJECT TITLE		:	16 x 2 Character LCD Controller
 Architecture		:	ARM7TDMI-S
 MCU				:	NXP's LPC2148
 Evaluation Kit		:	Blueboard from NGX Technologies
 Author				:	P V S Phaneendra
 Email ID			:	pvs.myworks@gmail.com
 Date of Creation	: 	16-Jan-2011
 LICENCE			:	Anyone is to use, copy, publish or modify this file as
 						long as this header isn't removed
********************************************************************************/

#include "Pvs_Delay.h"
#include "Pvs_16x2Lcd.h"

int main (void)
{
	unsigned char *dataPtr;

	// Input Parameters
	unsigned char numberOfLines		= 		2;	// Enter '1' for One Line Display and '2' for Two Line Display
	unsigned char characterFont		= 	0x58;	// Enter 0x58 for "5x8"	character font and 0x5A for "5x10"
	unsigned char cursorMovingDirection = 	1;	// Cursor Increment = 1; Cursor Decrement = 0;
	unsigned char displayShift		=		1;	// DisplayShift = 1; NoDisplayShift = 0;	
	unsigned char displayBit 		=		1;	// Display On = 1; Display Off = 0;
	unsigned char cursorBit	 		= 		1;	// Cursor On = 1; Cursor Off = 0;
	unsigned char blinkBit	 		=		1;	// Blinking On = 1; Blinking Off = 0;			
	unsigned char chooseCursorDisplay = 	1;	// CursorShift = 0; DisplayShift = 1;
	unsigned char chooseLeftRight	=		0;	// ChooseLeft = 0; ChooseRight = 1;
	unsigned char writeModeBit		=		0;	// For Contiguous Memory locations from 0x80 = 0; To specify location = 1; 
	unsigned char lineSelect 		=		1;	// Enter the Line number
	unsigned char characterLocation	= 		1;	// Character location in the line selected
	unsigned char *lcdText1 = "P V S PhAnEEnDrA";
	unsigned char *lcdText2 = "M.Tech IITR";

	PvsLcdBacklightOff(1000000);
	PvsLcdBacklightOn(1000000);
	PvsLcdSetUp(numberOfLines, characterFont);
	PvsLcdClearDisplay();
	PvsLcdReturnHome();
	PvsLcdEntryModeSet(cursorMovingDirection, displayShift);
	PvsLcdDisplayOnOffControl(displayBit, cursorBit, blinkBit);
	PvsLcdCursorDisplayShift(chooseCursorDisplay, chooseLeftRight);
	
	dataPtr = lcdText1;
	PvsLcdWriteModeSelect(writeModeBit, lineSelect, characterLocation, dataPtr);
	
	lineSelect = 2;
	dataPtr = lcdText2;
	PvsLcdWriteModeSelect(writeModeBit, lineSelect, characterLocation, dataPtr);
	
	while(1);
}
