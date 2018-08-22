/*******************************************************************************
 CLASS DEFINITION	:	16 x 2 Character LCD Function Set
 Architecture		:	ARM7TDMI-S
 MCU				:	NXP's LPC2148
 Evaluation Kit		:	Blueboard from NGX Technologies
 Author				:	P V S Phaneendra
 Email ID			:	pvs.myworks@gmail.com
 Date of Creation	: 	15-Jan-2011
 LICENCE			:	Anyone is to use, copy, publish or modify this file as
 						long as this header isn't removed
********************************************************************************/

#include "Pvs_16x2Lcd.h"

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
void PvsLcdBacklightOn(double timeDelay)
{
	IO1DIR	=	LCD_BL;
	IO1SET	= 	LCD_BL; 
	#ifdef _PVS_DELAY_H_
	PvsSetTimeDelay(timeDelay);
	#endif
}

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
void PvsLcdBacklightOff(double timeDelay)
{
	IO1DIR	= LCD_BL;
	IO1CLR	= LCD_BL; 
	#ifdef _PVS_DELAY_H_
	PvsSetTimeDelay(timeDelay);
	#endif
}

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
void PvsLcdClearDisplay(void)
{
	PvsLcdWriteCommand(0x01);
}

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
void PvsLcdReturnHome(void)
{
	PvsLcdWriteCommand(0x02);
}

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
void PvsLcdEntryModeSet(unsigned char cursorMovingDirection, unsigned char displayShift)
{
	unsigned char command = 0x4;
	command |= (cursorMovingDirection << 1)|(displayShift << 0); 
	PvsLcdWriteCommand(command);
}

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
void PvsLcdDisplayOnOffControl(unsigned char displayBit, unsigned char cursorBit, unsigned char blinkBit)
{
	unsigned char command = 0x8;
	command	|= (displayBit << 2)|(cursorBit << 1)|(displayBit << 0);
	PvsLcdWriteCommand(command);
}

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
void PvsLcdSetUp(unsigned char numberOfLines, unsigned char characterFont)
{
	PINSEL0 |= 0x00000000;
	PINSEL2 |= 0x00000000;

	IO1DIR	=	LCD_CMDPIN;
	IO1CLR	=	LCD_CMDPIN;
	IO0DIR	=	LCD_DATABUS;
	
	#ifdef _PVS_DELAY_H_
	PvsSetTimeDelay(10000);
	#endif

	if ((numberOfLines == 1)|(characterFont == 0x58))
		PvsLcdWriteCommand(0x20);
	else if ((numberOfLines == 1)|(characterFont == 0x5A))
		PvsLcdWriteCommand(0x24);
	else if (numberOfLines == 2)
		PvsLcdWriteCommand(0x28);
	
	#ifdef _PVS_DELAY_H_
	PvsSetTimeDelay(1000);	
	#endif
}

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
void PvsLcdCursorDisplayShift (unsigned char chooseCursorDisplay, unsigned char chooseLeftRight)
{
	unsigned char command = 0x10;
	command |= (chooseCursorDisplay << 3)|(chooseLeftRight << 2);
	PvsLcdWriteCommand(command);
}

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
void PvsLcdWriteModeSelect(unsigned char writeModeBit, unsigned char lineSelect, unsigned char characterLocation, unsigned char *dataPtr)
{
	unsigned char lcdAddress = 0x80;

	switch(writeModeBit)
	{
		case 0:	{
					lcdAddress	|=	((lineSelect - 1) << 6);
					while((*dataPtr) != '\0')
					{	
						PvsLcdWriteCommand(lcdAddress++);
						PvsLcdWriteData(*(dataPtr++));
						
						#ifdef _PVS_DELAY_H_
						PvsSetTimeDelay(100000);
						#endif
					}
				}
		case 1:	{
					lcdAddress	|=	((lineSelect - 1) << 6)|((characterLocation - 1) << 0);
					PvsLcdWriteCommand(lcdAddress);
					PvsLcdWriteData(*dataPtr); 	
				}
	}
}

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
void PvsLcdWriteCommand(unsigned char command)
{
	unsigned char temp1 = 0;
	unsigned long int temp2 = 0;

	temp1 = ((command >> 4) & 0x0F);
	temp2 = ((temp1 << 10) & LCD_DATABUS);

	IO1CLR	= (LCD_RS|LCD_RW);
	IO1SET	= LCD_EN;
	IO0CLR	= LCD_DATABUS;
	IO0SET	= temp2;
	#ifdef _PVS_DELAY_H_
	PvsSetTimeDelay(10000);
	#endif
	IO1CLR	= LCD_EN;
	
	temp1 = (command & 0x0F);
	temp2 = ((temp1 << 10) & LCD_DATABUS);
	#ifdef _PVS_DELAY_H_
	PvsSetTimeDelay(200);
	#endif

	IO1CLR	|= (LCD_RS|LCD_RW);
	IO1SET	|= LCD_EN;
	IO0CLR	= LCD_DATABUS;
	IO0SET	= temp2;
	#ifdef _PVS_DELAY_H_
	PvsSetTimeDelay(10000);
	IO1CLR	|= LCD_EN;
	#endif

	PvsLcdWaitForNextCommand();	
}

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
void PvsLcdWaitForNextCommand(void)
{
	IO1CLR	|=	LCD_RS;
	IO1SET	|=	(LCD_RW|LCD_EN);

	while(IO1PIN & (1 << 13));

	IO1DIR 	|= (LCD_RW|LCD_EN);
  	IO1DIR 	|= LCD_DATABUS;
}

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
void PvsLcdWriteData(unsigned char data)
{
	unsigned char temp1 = 0;
	unsigned long int temp2 = 0;

	temp1 = ((data >> 4) & 0x0F);
	temp2 = ((temp1 << 10) & LCD_DATABUS);

	IO1CLR	= LCD_RW;
	IO1SET	|= (LCD_RS|LCD_EN);
	IO0CLR	= LCD_DATABUS;
	IO0SET	= temp2;
	#ifdef _PVS_DELAY_H_
	PvsSetTimeDelay(10000);
	#endif
	IO1CLR	|= LCD_EN;
	
	temp1 = (data & 0x0F);
	temp2 = ((temp1 << 10) & LCD_DATABUS);
	#ifdef _VS_DELAY_H_
	PvsSetTimeDelay(200);
	#endif

	IO1CLR	= LCD_RW;
	IO1SET	|= (LCD_RS|LCD_EN);
	IO0CLR	= LCD_DATABUS;
	IO0SET	= temp2;
	#ifdef _PVS_DELAY_H_
	PvsSetTimeDelay(10000);
	#endif
	IO1CLR	|= LCD_EN;
	
	PvsLcdWaitForNextCommand();	
}
