// 	******************************************************************************************************************
//	NAME		   : P V S PHANEENDRA
// 	DESIGNATION    : GRADUATE ENGINEER TRAINEE
// 	COMPANY        : HITECH ROBOTIC SYSTEMZ LIMITED, GURGAON
// 	MODULE         : FUNCTIONS DEFINITION
//	VERSION		   : 1.0.1v	
// 	DATE OF DESIGN : 23rd MARCH, 2010 
// 	DESIGN TOOLS   : KEIL uVISION v3.23a, FLASH MAGIC NXP's SERIAL PROGRAMMER, HYPERTERMINAL SOFTWARE - XCTU
//	ARM CLASS	   : ARM7TDMI-S
//	TARGET CHIP	   : NXP's LPC2148
// 	DESCRIPTION    : THIS FILE LISTS ALL THE FUCNTION DEFINITIONS REGARDING USE OF PERIPHERALS FOR NXP'S LPC2148
//					 FOR THE NGX's BLUEBOARD IN PARTICULAR.
// 	LICENSE        : ANYONE IS TO COPY, USE OR PUBLISH THIS MODULE AS LONG AS THE HEADER OF THIS MODULE IS NOT REMOVED.
// ************************************************************************************************************************

#include <LPC214x.H>
#include "P_V_S_PHANEENDRA.h"

#define LCD_CMDPIN  ((1 << 24)|(1 << 23)|(1 << 22))
#define LCD_DATABUS	((1 << 13)|(1 << 12)|(1 << 11)|(1 << 10))

#define LCD_BL	(1 << 21)
#define LCD_EN	(1 << 22)
#define LCD_RW	(1 << 23)
#define LCD_RS	(1 << 24)

void setDelay (double);
void playBuzzer (unsigned char, double);
void configureSerialUart0 (double, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char);
void charTransmitFromUart0 (unsigned char);
unsigned char charReceiveAtUart0 (void); 
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

/////////////////////////////////////////////////////////////////////////////////
// //////////////////////// DELAY FUNCTION DEFINITION ///////////////////////////
void setDelay (double looptime)
{
	double i;
	for(i = 0; i <= looptime; i++);
}////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////
//////////////////////// BUZZER FUNCTION DEFINITION /////////////////////////////
void playBuzzer (unsigned char ON1_OFF0, double timedelay)
{
	IO1DIR	= 	0x02000000;
	if(ON1_OFF0)
	{
		IO1SET 	=	0x02000000;
		setDelay (timedelay);
	}
	else
	{
		IO1CLR	=	0x02000000;	
		setDelay (timedelay);
	}
}//////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////
///////////////////////// UART0 REGISTERS FUNCTIONS DEFINITIONS ///////////////////

// ---------------------- UART0 CONFIGURATION FUNCTION DECLARATION ---------------- 
void configureSerialUart0 (double baudrate, unsigned char breakControl, unsigned char paritySelect, unsigned char parityEnable, unsigned char stopBitSelect, unsigned char wordLengthSelect)
{
	PINSEL0 |= 0x00000005;
	VPBDIV	= 0x0;
	
	// Registers setting for customized baudrate of 9600 bauds/sec
	U0LCR = 0x80;		   // Set DLAB = 1 for configuring U0DLM:U0DLL

	if (baudrate == 1200)	{ 
				U0DLM = 0x03; U0DLL = 0x0D; }
	else if (baudrate == 2400)	{
				U0DLM = 0x01; U0DLL = 0x86; }
	else if (baudrate == 4800)	{
				U0DLM = 0x00; U0DLL = 195;  }
	else if (baudrate == 9600)	{ 
				U0DLM = 0x00; U0DLL = 97;   }
	else if (baudrate == 19200)	{
				U0DLM = 0x00; U0DLL = 48;   }
	else if (baudrate == 38400)	{
				U0DLM = 0x00; U0DLL = 24;   }
	else if (baudrate == 57600)	{
				U0DLM = 0x00; U0DLL = 16;   }
	else if (baudrate == 115200)	{
				U0DLM = 0x00; U0DLL = 8;    }
	else if (baudrate == 230400)	{
				U0DLM = 0x00; U0DLL = 4;    }

	U0FCR = 0x07;		   
	U0LCR = (0 << 7)|(breakControl << 6)|(paritySelect << 4)|(parityEnable << 3)|((stopBitSelect - 1) << 2)|((wordLengthSelect - 5) << 0);
}

// ----------------- UART0 TRANSMITTER FUNCTION -----------------
void charTransmitFromUart0 (unsigned char data)
{
	while(!(U0LSR & 0x20));
	U0THR = data;
}

// ------------------- UART0 RECEIVER FUNCTION ------------------
unsigned char charReceiveAtUart0 (void)
{
	while(!(U0LSR & 0x01));
	return(U0RBR);
}////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////// 16x2 CHARACTER DISPLAY FUNCTIONS //////////////////////////

// --------------------------- LCD BACKLIGHT ON FUNCTION DEFINITION ----------------------
void lcdBacklightOn(double timeDelay)
{
	IO1DIR	=	LCD_BL;
	IO1SET	= 	LCD_BL; 
	setDelay(timeDelay);
}

// --------------------------- LCD BACKLIGHT OFF FUNCTION DEFINITION ---------------------
void lcdBacklightOff(double timeDelay)
{
	IO1DIR	= LCD_BL;
	IO1CLR	= LCD_BL; 
	setDelay(timeDelay);
} 
 
// -------------------------------- LCD CLEAR DISPLAY DEFINITION -----------------------
void lcdClearDisplay(void)
{
	lcdWriteCommand(0x01);
}

// ----------------------------- LCD CURSOR RETURN HOME DEFINITION ---------------------
void lcdReturnHome(void)
{
	lcdWriteCommand(0x02);
}

// ---------------------------- LCD ENTRY MODE SET DEFINITION --------------------------
void lcdEntryModeSet(unsigned char cursorMovingDirection, unsigned char displayShift)
{
	unsigned char command = 0x4;
	command |= (cursorMovingDirection << 1)|(displayShift << 0); 
	lcdWriteCommand(command);
}

// ---------------------------- LCD DISPLAY ON-OFF CONTROL FUNCTION DEFINITION ------------------------
void lcdDisplayOnOffControl(unsigned char displayBit, unsigned char cursorBit, unsigned char blinkBit)
{
	unsigned char command = 0x8;
	command	|= (displayBit << 2)|(cursorBit << 1)|(displayBit << 0);
	lcdWriteCommand(command);
}

// ---------------------------- LCD CURSOR DISPLAY SHIFT FUNCTION DEFINITION ------------------------
void lcdCursorDisplayShift (unsigned char chooseCursorDisplay, unsigned char chooseLeftRight)
{
	unsigned char command = 0x10;
	command |= (chooseCursorDisplay << 3)|(chooseLeftRight << 2);
	lcdWriteCommand(command);
}

// ------------------------------- LCD SETUP FUNCTION DEFINITION -------------------------
void lcdSetUp(unsigned char numberOfLines, unsigned char characterFont)
{
	unsigned char command = 0x20;	

	PINSEL0 |= 0x00000000;
	PINSEL2 |= 0x00000000;

	IO1DIR	=	LCD_CMDPIN;
	IO1CLR	=	LCD_CMDPIN;
	IO0DIR	=	LCD_DATABUS;
	
	setDelay(10000);

	if ((numberOfLines == 1)|(characterFont == 0x58))
		lcdWriteCommand(0x20);
	else if ((numberOfLines == 1)|(characterFont == 0x5A))
		lcdWriteCommand(0x24);
	else if (numberOfLines == 2)
		lcdWriteCommand(0x28);
	setDelay(1000);	
}

// ------------------------------------------- LCD WRITE MODE SELECT FUNCTION DEFINITION ---------------------------------------------
void lcdWriteModeSelect(unsigned char writeModeBit, unsigned char lineSelect, unsigned char characterLocation, unsigned char *dataPtr)
{
	unsigned char lcdAddress = 0x80;

	switch(writeModeBit)
	{
		case 0:	{
					lcdAddress	|=	((lineSelect - 1) << 6);
					while((*dataPtr) != '\0')
					{	
						lcdWriteCommand(lcdAddress++);
						lcdWriteData(*(dataPtr++));
						setDelay(100000);
					}
				}
		case 1:	{
					lcdAddress	|=	((lineSelect - 1) << 6)|((characterLocation - 1) << 0);
					lcdWriteCommand(lcdAddress);
					lcdWriteData(*dataPtr); 	
				}
	}
}

// --------------- LCD WRITE COMMAND FUNCTION DEFINITION -------------------
void lcdWriteCommand(unsigned char command)
{
	unsigned char temp1 = 0;
	unsigned long int temp2 = 0;

	temp1 = ((command >> 4) & 0x0F);
	temp2 = ((temp1 << 10) & LCD_DATABUS);

	IO1CLR	= (LCD_RS|LCD_RW);
	IO1SET	= LCD_EN;
	IO0CLR	= LCD_DATABUS;
	IO0SET	= temp2;
	setDelay(10000);
	IO1CLR	= LCD_EN;
	
	temp1 = (command & 0x0F);
	temp2 = ((temp1 << 10) & LCD_DATABUS);
	setDelay(200);

	IO1CLR	|= (LCD_RS|LCD_RW);
	IO1SET	|= LCD_EN;
	IO0CLR	= LCD_DATABUS;
	IO0SET	= temp2;
	setDelay(10000);
	IO1CLR	|= LCD_EN;
	lcdWaitForNextCommand();	
}

// ---------------- LCD WRITE DATA FUNCTION --------------------
void lcdWriteData(unsigned char data)
{
	unsigned char temp1 = 0;
	unsigned long int temp2 = 0;

	temp1 = ((data >> 4) & 0x0F);
	temp2 = ((temp1 << 10) & LCD_DATABUS);

	IO1CLR	= LCD_RW;
	IO1SET	|= (LCD_RS|LCD_EN);
	IO0CLR	= LCD_DATABUS;
	IO0SET	= temp2;
	setDelay(10000);
	IO1CLR	|= LCD_EN;
	
	temp1 = (data & 0x0F);
	temp2 = ((temp1 << 10) & LCD_DATABUS);
	setDelay(200);

	IO1CLR	= LCD_RW;
	IO1SET	|= (LCD_RS|LCD_EN);
	IO0CLR	= LCD_DATABUS;
	IO0SET	= temp2;
	setDelay(10000);
	IO1CLR	|= LCD_EN;
	
	lcdWaitForNextCommand();	
}

// ------------------- LCD WAIT FOR NEXT COMMAND FUNCTION DEFINITION -----------------
void lcdWaitForNextCommand(void)
{
	IO1CLR	|=	LCD_RS;
	IO1SET	|=	(LCD_RW|LCD_EN);

	while(IO1PIN & (1 << 13));

	IO1DIR 	|= (LCD_RW|LCD_EN);
  	IO1DIR 	|= LCD_DATABUS;
}
////////////////////////////////////////////////////////////////////////////////////
