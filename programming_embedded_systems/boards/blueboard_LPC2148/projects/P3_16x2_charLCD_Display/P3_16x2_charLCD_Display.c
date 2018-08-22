// 	******************************************************************************************************************
//	NAME		   : P V S PHANEENDRA
// 	DESIGNATION    : GRADUATE ENGINEER TRAINEE
// 	COMPANY        : HITECH ROBOTIC SYSTEMZ LIMITED, GURGAON
// 	MODULE         : 16x2 Character LCD Interfacing using KEIL on NGX's Blueboard (LPC2148)
// 	DATE OF DESIGN : 23rd MARCH, 2010 
// 	DESIGN TOOLS   : KEIL uVISION v3.23a, FLASH MAGIC NXP's SERIAL PROGRAMMER, HYPERTERMINAL SOFTWARE - XCTU
//	ARM CLASS	   : ARM7TDMI-S
//	TARGET CHIP	   : NXP's LPC2148
// 	DESCRIPTION    : THIS FILE LISTS ALL THE FUCNTION DEFINITIONS FOR 16X2 CHARACTER LCD INTERFACING WITH NXP'S 
//					 LPC2148 FOR THE NGX's BLUEBOARD IN PARTICULAR.
// 	LICENSE        : ANYONE IS TO COPY, USE OR PUBLISH THIS MODULE AS LONG AS THE HEADER OF THIS MODULE IS NOT REMOVED.
// *******************************************************************************************************************

#include <LPC214X.H>  
#include "P_V_S_Phaneendra.h"

void setDelay(double);
void lcdSetUp(unsigned char, unsigned char);
void lcdBacklightOn(double);
void lcdBacklightOff(double);
void lcdClearDisplay(void);
void lcdReturnHome(void);
void lcdEntryModeSet(unsigned char, unsigned char);
void lcdDisplayOnOffControl(unsigned char, unsigned char, unsigned char);
void lcdCursorDisplayShift (unsigned char, unsigned char);
void lcdWriteModeSelect(unsigned char, unsigned char, unsigned char, unsigned char *);
void lcdWriteCommand(unsigned char);
void lcdWaitForNextCommand(void);
void lcdWriteData(unsigned char);

int main(void)
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
	unsigned char chooseCursorDisplay = 	0;	// CursorShift = 0; DisplayShift = 1;
	unsigned char chooseLeftRight	=		1;	// ChooseLeft = 0; ChooseRight = 1;
	unsigned char writeModeBit		=		0;	// For Contiguous Memory locations from 0x80 = 0; To specify location = 1; 
	unsigned char lineSelect 		=		1;	// Enter the Line number
	unsigned char characterLocation	= 		1;	// Character location in the line selected
	unsigned char *lcdText1 = "P V S PhAnEEnDrA";
	unsigned char *lcdText2 = "M.Tech IITR";

	lcdBacklightOff(1000000);
	lcdBacklightOn(1000400);
	lcdSetUp(numberOfLines, characterFont);
	lcdClearDisplay();
	lcdReturnHome();
	lcdEntryModeSet(cursorMovingDirection, displayShift);
	lcdDisplayOnOffControl(displayBit, cursorBit, blinkBit);
	lcdCursorDisplayShift(chooseCursorDisplay, chooseLeftRight);
	
	dataPtr = lcdText1;
	lcdWriteModeSelect(writeModeBit, lineSelect, characterLocation, dataPtr);
	
	lineSelect = 2;
	dataPtr = lcdText2;
	lcdWriteModeSelect(writeModeBit, lineSelect, characterLocation, dataPtr);
	
	while(1);
} 
