// 	******************************************************************************************************************
//	NAME	       : P V S PHANEENDRA
// 	MODULE         : FUNCTIONS DEFINITION
//	VERSION	       : 1.0.3v	
// 	DATE OF DESIGN : 4th APRIL, 2010 
// 	DESIGN TOOLS   : KEIL uVISION v3.23a, FLASH MAGIC NXP's SERIAL PROGRAMMER, HYPERTERMINAL SOFTWARE - XCTU
//	ARM CLASS      : ARM7TDMI-S
//	TARGET CHIP    : NXP's LPC2148
// 	DESCRIPTION    : THIS FILE LISTS ALL THE FUCNTION DEFINITIONS REGARDING USE OF PERIPHERALS FOR NXP'S LPC2148
//			 FOR THE NGX's BLUEBOARD IN PARTICULAR.
// 	LICENSE        : ANYONE IS TO COPY, USE OR PUBLISH THIS MODULE AS LONG AS THE HEADER OF THIS MODULE IS NOT REMOVED.
// ************************************************************************************************************************

/* ------------------------------------------------------------------------------------------------------------------------
     The following functionalities that have been appended to the present version v1.0.2 are stated below:
	a.	Function prototype & definition to initialize the type of interrupt source.
	b.	Function prototype & definition for pin selection register of the corresponding interrupt source selected
	c.	Function prototype & definition for VIC interrupt select register settings
	d.	Function prototype & definition for VIC interrupt enable register settings
 	e.	Function prototype & definition for EXT_IRQ6 funCtion
	f.	Function prototype & definition for EXT_IRQ16 function
   ---------------------------------------------------------------------------------------------------------------------- */

#include <LPC214x.H>

// --------------- 16x2 Character LCD I/O Connections Description ----------
#define LCD_CMDPIN  ((1 << 24)|(1 << 23)|(1 << 22))
#define LCD_DATABUS	((1 << 13)|(1 << 12)|(1 << 11)|(1 << 10))

#define LCD_BL	(1 << 21)
#define LCD_EN	(1 << 22)
#define LCD_RW	(1 << 23)
#define LCD_RS	(1 << 24)
// -------------------------------------------------------------------------
#define enableVectIRQBit	(1	<< 	5)


// -----------------------------------------------------------------------------------------------------------
void setDelay (double);
// ___________________________________________________________________________________________________________
void playBuzzer (unsigned char);
// ___________________________________________________________________________________________________________
void configureSerialUart0 (double, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char);
void charTransmitFromUart0 (unsigned char);
unsigned char charReceiveAtUart0 (void); 
void checkDoubleWord (unsigned long int);
// ___________________________________________________________________________________________________________
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
// ___________________________________________________________________________________________________________
void initVICInterruptSource (unsigned char);
void pinSelectInterruptSource (unsigned char);
void regVICInterruptSelect (unsigned char, unsigned char);
void regVICInterruptEnable (unsigned char);
void EXT_IRQ6 (void) __irq;
void EXT_IRQ16 (void) __irq;
// -----------------------------------------------------------------------------------------------------------


/////////////////////////////////////////////////////////////////////////////////
/////////////////////////// DELAY FUNCTION DEFINITION ///////////////////////////

void setDelay (double looptime)
{
	double i;
	for(i = 0; i <= looptime; i++);
}////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////
//////////////////////// BUZZER FUNCTION DEFINITION /////////////////////////////

// -------------------------- PLAY BUZZER FUNCTION DEFINITION ---------------------
void playBuzzer (unsigned char ON1_OFF0)
{
	IO1DIR	= 	0x02000000;
	if(ON1_OFF0)
		IO1SET 	=	0x02000000;
	else
		IO1CLR	=	0x02000000;	
}//////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////
///////////////////////// UART0 REGISTERS FUNCTIONS DEFINITIONS ///////////////////

// ---------------------- UART0 CONFIGURATION FUNCTION DECLARATION ---------------- 
void configureSerialUart0 (double baudrate, unsigned char breakControl, unsigned char paritySelect, unsigned char parityEnable, unsigned char stopBitSelect, unsigned char wordLengthSelect)
{
	PINSEL0 |= 0x00000005;
	VPBDIV	= 0x00;
	
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

// ----------------- UART0 TRANSMITTER FUNCTION DEFINITION -----------------
void charTransmitFromUart0 (unsigned char data)
{
	while(!(U0LSR & 0x20));
	U0THR = data;
}

// ------------------- UART0 RECEIVER FUNCTION DEFINITION ------------------
unsigned char charReceiveAtUart0 (void)
{
	while(!(U0LSR & 0x01));
	return(U0RBR);
}

// --------------------------- DEFINITION OF FUNCTIONS USEFUL FOR DEBUGGING ------------------------------
void checkDoubleWord (unsigned long int doubleWord)
{
	unsigned char byte = 0, i = 0;
	while(i < 4)
	{
		byte = (unsigned)(doubleWord >> (i*8));		
		charTransmitFromUart0 (byte);
		i++;
	}
}/////////////////////////////////////////////////////////////////////////////////////////////////////////


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
}//////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// VECTORED INTERRUPT CONTROLLER (VIC) //////////////////////////////////////
// ------------- Connection of Interrupt Sources to the Vectored Interrupt Controller (VIC) -------------------
//	watchdogInterrupt	VIC_Mask = 	0
//  softwareInterrupt	VIC_Mask =	1
//	embdICE_dbgCommRx	VIC_Mask =	2
//	embdICE_dbgCommTx	VIC_Mask =	3
// 	TIMER0				VIC_Mask =	4
// 	TIMER1				VIC_Mask =	5
// 	UART0				VIC_Mask =	6
// 	UART1				VIC_Mask =	7
//	PWM0				VIC_Mask =	8
// 	I2C0				VIC_Mask =	9
//	SPI0				VIC_Mask =	10
//	SP1 (SSP)			VIC_Mask =	11
//	PLL					VIC_Mask =	12
//	RTC					VIC_Mask =	13
//	EINT0				VIC_Mask =	14
//	EINT1				VIC_Mask =	15
//	EINT2				VIC_Mask =	16
//	EINT3				VIC_Mask =	17
//	ADC0				VIC_Mask =	18
//	I2C1				VIC_Mask =	19
//	BOD					VIC_Mask =	20
//	ADC1				VIC_Mask =	21
//	USB					VIC_Mask =	22
// ------------------------------------------------------------------------------------------------------------

// ---------------------------- INITIALIZE VIC VECTORED INTERRUPT SOURCES	-----------------------------------
void initVICInterruptSource (unsigned char interruptSourceType) 
{
	switch(interruptSourceType)
	{
		case	6:	{
	
						// ______________________ UART0 EXTERNAL INTERRUPT - IRQ#6 __________________________________ 
   	
						// Selecting the Pin (Port0) A.15 for connecting to a User Interface Switch
						pinSelectInterruptSource(interruptSourceType);	
	
						U0IER	=	0x3;

						// Argument#1: IRQ = 0/ FIQ = 1; Argument#2: VICInterruptSourceType
						//Classifying all interrupts as General Purpose IRQs
						regVICInterruptSelect(0,interruptSourceType);		

						// Writing to the Vector Controller register
						// Enables the Vector Interrupt Controller with assigned priority level (Highest = 0)
						VICVectCntl0	=	(enableVectIRQBit)|(interruptSourceType);		

						// Stores the vectored address of the C function when the interrupt occurs
						VICVectAddr0 	= 	(unsigned)EXT_IRQ6;   
	
						// Enables the ARM7 CPU for EINT1 class external interrupt
						regVICInterruptEnable (interruptSourceType);
							
						break;
					}

		case	16:	{
						// _______________________ EXTERNAL INTERRUPT#2 (EINT2) - IRQ#16  ___________________________
   					
						// Selecting the Pin (Port0) A.15 for connecting to a User Interface Switch
						pinSelectInterruptSource(interruptSourceType);	
	
						// Setting the Registers
						EXTMODE	|=	(0 << 2);			// Level - Triggered = 0; Edge - Triggered = 1;
						EXTPOLAR |= (0 << 2);			// Falling Edge/ Low Level = 0; Rising Edge/ High Level = 1;
	
						// Argument#1: IRQ = 0/ FIQ = 1; Argument#2: VICInterruptSourceType
						//Classifying all interrupts as General Purpose IRQs
						regVICInterruptSelect(0,interruptSourceType);		

						// Writing to the Vector Controller register
						// Enables the Vector Interrupt Controller with assigned priority level (Highest = 0)
						VICVectCntl1	=	(enableVectIRQBit)|(interruptSourceType);		

						// Stores the vectored address of the C function when the interrupt occurs
						VICVectAddr1 	= 	(unsigned)EXT_IRQ16;   
	
						// Enables the ARM7 CPU for EINT1 class external interrupt
						regVICInterruptEnable (interruptSourceType);

						EXTINT	|=	(0 << 2);

						break;
					}
	}
}

// -------------------------- PIN SELECT FUNCTION FOR INTERRUPT SOURCES DEFINITION ----------------------------
void pinSelectInterruptSource (unsigned char interruptMaskType)
{
	switch(interruptMaskType)
	{
		case 6	:{	
					PINSEL0	|=	(5 << 0);
					break;
				 }
		
		case 14	:{  	
					PINSEL0	|=	(3 << 2);	
					PINSEL1	|=	(1 << 0);
					break;
				 }
		case 15	:{  	
					PINSEL0	|=	(2 << 28)|(3 << 6);
					break;
				 }
		case 16	:{  	
					PINSEL0	|=	((unsigned)2 << 30)|((unsigned)3 << 14);
					break;
		         }
		case 17	:{  	
					PINSEL0	|=	(3 << 18);	
					PINSEL1	|=	(2 << 28)|(3 << 8);
					break;
				 }	
	}
}


// ---------------------------- SETTING INTERRUPT REQUEST TYPE FUNCTION DEFINITION ----------------------------
void regVICInterruptSelect (unsigned char IRQ0_FIQ1, unsigned char interruptMaskType)
{
	VICIntSelect	|=	((unsigned)IRQ0_FIQ1 << interruptMaskType);
}


// --------------------------------- VIC VECTOR ENABLE FUNCTION DEFINITION ------------------------------------
void regVICInterruptEnable (unsigned char interruptMaskType)
{
	VICIntEnable 	|= 	(1 << interruptMaskType);	
}

// ----------------------------- C FUNCTION FOR THE EXT_IRQ6 (EINT2) FUNCTION DEFINITION ---------------------
void EXT_IRQ6 (void) __irq
{
	// BUZZER PLAY
	IO1DIR = 0x02000000;
	IO1CLR = 0x02000000;
	setDelay(1000);
	IO1SET = 0x02000000;
	setDelay(10000);
	IO1CLR = 0x02000000;

	EXTINT		|=	(1 << 2);
	VICVectAddr	=	0x00000000;
}

// --------------------------- C FUNCTION FOR THE EXT_IRQ16 UART0 FUNCTION DEFINITION ------------------------
void EXT_IRQ16 (void) __irq
{
	unsigned char temp1 = 0, temp2 = 0;
	
	temp1	=	U0IIR;
	temp1	=	(temp1 >> 1) & 0x7;

	switch(temp1)
	{
		case	6:	break;									// CTI - C
		case	2:	{										// RDA - Read Data Available
						temp2	=	charReceiveAtUart0();
						charTransmitFromUart0 (temp2);
						break;
					}
		case	1:	break;									// THRE	- Transmitter Holding Register Empty
	}
	VICVectAddr	=	0x00000000;
}


