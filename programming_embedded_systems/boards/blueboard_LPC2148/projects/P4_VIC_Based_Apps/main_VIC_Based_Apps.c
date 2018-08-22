#include <LPC214x.H>
#include "P_V_S_Phaneendra.h"

void setDelay (double);
void configureSerialUart0 (double, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char);
unsigned char charReceiveAtUart0 (void);
void charTransmitFromUart0 (unsigned char);
void checkDoubleWord (unsigned long int);
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
void pinSelectInterruptSource (unsigned char);
void regVICInterruptSelect (unsigned char, unsigned char);
void regVICInterruptEnable (unsigned char);
void initVICInterruptSource (unsigned char);

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
	unsigned char *lcdText1 = "P V S Phaneendra";
	unsigned char *lcdText2 = "M.Tech IIIR";

	// Check the manual before entering the interrupt source types
	unsigned char interruptSourceType = 6;	
	initVICInterruptSource (interruptSourceType);
	interruptSourceType = 16;
	initVICInterruptSource (interruptSourceType);
	
	configureSerialUart0 (9600, 0, 0, 0, 1, 8);

	// ___________________________________________________________________________________
	while(1)
	{
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
	}
}

