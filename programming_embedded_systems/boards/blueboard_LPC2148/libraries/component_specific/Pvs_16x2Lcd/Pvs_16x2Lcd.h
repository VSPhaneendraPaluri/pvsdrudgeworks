/*******************************************************************************
 CLASS HEADER		:	16 x 2 Character LCD Function Set
 Architecture		:	ARM7TDMI-S
 MCU				:	NXP's LPC2148
 Evaluation Kit		:	Blueboard from NGX Technologies
 Author				:	P V S Phaneendra
 Email ID			:	pvs.myworks@gmail.com
 Date of Creation	: 	15-Jan-2011
 LICENCE			:	Anyone is to use, copy, publish or modify this file as
 						long as this header isn't removed
********************************************************************************/

#ifndef _PVS_16x2LCD_H_
#define _PVS_16x2LCD_H_

#include <lpc214x.h>
#include "Pvs_Delay.h"

#define LCD_CMDPIN  ((1 << 24)|(1 << 23)|(1 << 22))
#define LCD_DATABUS	((1 << 13)|(1 << 12)|(1 << 11)|(1 << 10))

#define LCD_BL	(1 << 21)				// LCD Blinking Enable PIN
#define LCD_EN	(1 << 22)				// LCD Enable PIN
#define LCD_RW	(1 << 23)				// LCD Read Write PIN
#define LCD_RS	(1 << 24)				// LCD Read Select

/*******************************************************************************
 FUNCTION			:	Configures the 16 x 2 Character LCD 
 Input Parameter(s)	:	Number Of Lines, Characer Font Selection
 Output Parameter(s):	Not Applicable
 Description		:	Choose between '0' & '1' for Number of Lines Selection
 						and for Character Font Selection, select between
						'0x58' for 5 (columns) x 8 (rows) and '0x5A' for 
						5 (columns) x 10 (rows) pixels
 Architecture		:	ARM7TDMI-S
 MCU				:	NXP's LPC2148
 Evaluation Kit		:	Blueboard from NGX Technologies
 Author				:	P V S Phaneendra
 Email ID			:	pvs.myworks@gmail.com
 Date of Creation	: 	15-Jan-2011
 LICENCE			:	Anyone is to use, copy, publish or modify this file as
 						long as this header isn't removed
********************************************************************************/
void PvsLcdSetUp(unsigned char, unsigned char);

/*******************************************************************************
 FUNCTION			:	Time to keep the LCD backlight On
 Input Parameter(s)	:	Time (in ms)
 Output Parameter(s):	Not Applicable
 Architecture		:	ARM7TDMI-S
 MCU				:	NXP's LPC2148
 Evaluation Kit		:	Blueboard from NGX Technologies
 Author				:	P V S Phaneendra
 Email ID			:	pvs.myworks@gmail.com
 Date of Creation	: 	15-Jan-2011
 LICENCE			:	Anyone is to use, copy, publish or modify this file as
 						long as this header isn't removed
********************************************************************************/
void PvsLcdBacklightOn(double);

/*******************************************************************************
 FUNCTION			:	Time to keep the LCD backlight off
 Input Parameter(s)	:	Time (in ms)
 Output Parameter(s):	Not Applicable
 Architecture		:	ARM7TDMI-S
 MCU				:	NXP's LPC2148
 Evaluation Kit		:	Blueboard from NGX Technologies
 Author				:	P V S Phaneendra
 Email ID			:	pvs.myworks@gmail.com
 Date of Creation	: 	15-Jan-2011
 LICENCE			:	Anyone is to use, copy, publish or modify this file as
 						long as this header isn't removed
********************************************************************************/
void PvsLcdBacklightOff(double);

/*******************************************************************************
 FUNCTION			:	Clears the LCD Display
 Input Parameter(s)	:	Not Applicable
 Output Parameter(s):	Not Applicable
 Architecture		:	ARM7TDMI-S
 MCU				:	NXP's LPC2148
 Evaluation Kit		:	Blueboard from NGX Technologies
 Author				:	P V S Phaneendra
 Email ID			:	pvs.myworks@gmail.com
 Date of Creation	: 	15-Jan-2011
 LICENCE			:	Anyone is to use, copy, publish or modify this file as
 						long as this header isn't removed
********************************************************************************/
void PvsLcdClearDisplay(void);

/*******************************************************************************
 FUNCTION			:	Returns the LCD cursor to the Top-Left of the LCD Screen
 Input Parameter(s)	:	Not Applicable
 Output Parameter(s):	Not Applicable
 Architecture		:	ARM7TDMI-S
 MCU				:	NXP's LPC2148
 Evaluation Kit		:	Blueboard from NGX Technologies
 Author				:	P V S Phaneendra
 Email ID			:	pvs.myworks@gmail.com
 Date of Creation	: 	15-Jan-2011
 LICENCE			:	Anyone is to use, copy, publish or modify this file as
 						long as this header isn't removed
********************************************************************************/
void PvsLcdReturnHome(void);

/*******************************************************************************
 FUNCTION			:	Provides selection parameters for Cursor Increment/Decrement
 						and Display Shift On/Off
 Input Parameter(s)	:	Cursor Increment/Decrement, Display Shift On/Off
 Output Parameter(s):	Not Applicable
 Description		:	'0' if Cursor Decrement and '1' if Cursor Increment;
 						'0' if Display Shift Off and '1' if Display Shift On
 Architecture		:	ARM7TDMI-S
 MCU				:	NXP's LPC2148
 Evaluation Kit		:	Blueboard from NGX Technologies
 Author				:	P V S Phaneendra
 Email ID			:	pvs.myworks@gmail.com
 Date of Creation	: 	15-Jan-2011
 LICENCE			:	Anyone is to use, copy, publish or modify this file as
 						long as this header isn't removed
********************************************************************************/
void PvsLcdEntryModeSet(unsigned char, unsigned char);

/*******************************************************************************
 FUNCTION			:	Sets Display On/Off, Cursor On/Off & Blinking On/Off
 Input Parameter(s)	:	Display On/Off bit, Cursor On/Off bit, Blinking On/Off bit
 Output Parameter(s):	Not Applicable
 Description		:	'0' if Display Off and '1' if Display On;
 						'0' if Cursor Off and '1' if Cursor On;
						'0' if Blinking Off and '1' if Blinking On
 Architecture		:	ARM7TDMI-S
 MCU				:	NXP's LPC2148
 Evaluation Kit		:	Blueboard from NGX Technologies
 Author				:	P V S Phaneendra
 Email ID			:	pvs.myworks@gmail.com
 Date of Creation	: 	02-Jan-2011
 LICENCE			:	Anyone is to use, copy, publish or modify this file as
 						long as this header isn't removed
********************************************************************************/
void PvsLcdDisplayOnOffControl(unsigned char, unsigned char, unsigned char);

/*******************************************************************************
 FUNCTION			:	Provides selection parameters for Cursor Shift Left/Right
 						and Display Shift Left/Right
 Input Parameter(s)	:	Cursor/Display Shift Control, Left/Right Shift Control
 Output Parameter(s):	Not Applicable
 Description		:	'0' if Cursor Shift and '1' if Display Shift;
 						'0' if Left Shift and '1' if Right Shift
 Architecture		:	ARM7TDMI-S
 MCU				:	NXP's LPC2148
 Evaluation Kit		:	Blueboard from NGX Technologies
 Author				:	P V S Phaneendra
 Email ID			:	pvs.myworks@gmail.com
 Date of Creation	: 	15-Jan-2011
 LICENCE			:	Anyone is to use, copy, publish or modify this file as
 						long as this header isn't removed
********************************************************************************/
void PvsLcdCursorDisplayShift (unsigned char, unsigned char);

/*******************************************************************************
 FUNCTION			:	Provides selection parameters for writing to LCD Character
 						Display
 Input Parameter(s)	:	Write Mode Bit, Line Select Bit, Character Location Select
 Output Parameter(s):	Not Applicable
 Description		:	'0' if Sequential Memory Write and '1' if X-Y Location;
 						'1' if Line 1 and '2' if Line 2; 
						Character X-Y Location;
						LCD Text/Data to be Displayed
 Architecture		:	ARM7TDMI-S
 MCU				:	NXP's LPC2148
 Evaluation Kit		:	Blueboard from NGX Technologies
 Author				:	P V S Phaneendra
 Email ID			:	pvs.myworks@gmail.com
 Date of Creation	: 	15-Jan-2011
 LICENCE			:	Anyone is to use, copy, publish or modify this file as
 						long as this header isn't removed
********************************************************************************/
void PvsLcdWriteModeSelect(unsigned char, unsigned char, unsigned char, unsigned char *);

/*******************************************************************************
 FUNCTION			:	Commands/Instruction Set for LCD Character Display
 Input Parameter(s)	:	LCD Command/Instruction
 Output Parameter(s):	Not Applicable
 Architecture		:	ARM7TDMI-S
 MCU				:	NXP's LPC2148
 Evaluation Kit		:	Blueboard from NGX Technologies
 Author				:	P V S Phaneendra
 Email ID			:	pvs.myworks@gmail.com
 Date of Creation	: 	15-Jan-2011
 LICENCE			:	Anyone is to use, copy, publish or modify this file as
 						long as this header isn't removed
********************************************************************************/
void PvsLcdWriteCommand(unsigned char);

/*******************************************************************************
 FUNCTION			:	Provides necessary delay between successive LCD Commands
 Input Parameter(s)	:	Not Applicable
 Output Parameter(s):	Not Applicable
 Architecture		:	ARM7TDMI-S
 MCU				:	NXP's LPC2148
 Evaluation Kit		:	Blueboard from NGX Technologies
 Author				:	P V S Phaneendra
 Email ID			:	pvs.myworks@gmail.com
 Date of Creation	: 	15-Jan-2011
 LICENCE			:	Anyone is to use, copy, publish or modify this file as
 						long as this header isn't removed
********************************************************************************/
void PvsLcdWaitForNextCommand(void);

/*******************************************************************************
 FUNCTION			:	Provides command to write data to the LCD Display
 Input Parameter(s)	:	LCD Text
 Output Parameter(s):	Not Applicable
 Architecture		:	ARM7TDMI-S
 MCU				:	NXP's LPC2148
 Evaluation Kit		:	Blueboard from NGX Technologies
 Author				:	P V S Phaneendra
 Email ID			:	pvs.myworks@gmail.com
 Date of Creation	: 	15-Jan-2011
 LICENCE			:	Anyone is to use, copy, publish or modify this file as
 						long as this header isn't removed
********************************************************************************/
void PvsLcdWriteData(unsigned char);

#endif
