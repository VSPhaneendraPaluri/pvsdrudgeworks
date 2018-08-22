// 	******************************************************************************************************************
//	NAME		   : P V S PHANEENDRA
// 	DESIGNATION    : GRADUATE ENGINEER TRAINEE
// 	COMPANY        : HITECH ROBOTIC SYSTEMZ LIMITED, GURGAON
// 	MODULE         : FUNCTIONS DEFINITION
//	VERSION		   : 1.0.0v	
// 	DATE OF DESIGN : 11th MARCH, 2010 
// 	DESIGN TOOLS   : KEIL uVISION v3.23a, FLASH MAGIC NXP's SERIAL PROGRAMMER, HYPERTERMINAL SOFTWARE - XCTU
//	ARM CLASS	   : ARM7TDMI-S
//	TARGET CHIP	   : NXP's LPC2148
// 	DESCRIPTION    : THIS FILE LISTS ALL THE FUCNTION DEFINITIONS REGARDING USE OF PERIPHERALS FOR NXP'S LPC2148
//					 FOR THE NGX's BLUEBOARD IN PARTICULAR.
// 	LICENSE        : ANYONE IS TO COPY, USE OR PUBLISH THIS MODULE AS LONG AS THE HEADER OF THIS MODULE IS NOT REMOVED.
// *******************************************************************************************************************

#include <LPC214x.h>

void setDelay (double);
void playBuzzer (unsigned char, double);
void configureSerialUart0 (double, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char);
void charTransmitFromUart0 (unsigned char);
unsigned char charReceiveAtUart0 (void);

// ------------------------ DELAY FUNCTION DEFINITION ----------------------
void setDelay (double looptime)
{
	double i;
	for(i = 0; i <= looptime; i++);
}

// ------------------- BUZZER FUNCTION DEFINITION -------------------------
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
}

// ---------------- UART0 CONFIGURATION FUNCTION DEFINITION ----------------
void configureSerialUart0 (double baudrate, unsigned char breakControl, unsigned char paritySelect, unsigned char parityEnable, unsigned char stopBitSelect, unsigned char wordLengthSelect)
{
	PINSEL0 = 0x00000005;
	VPBDIV	= 0x00;
	
	// Registers setting for customized baudrate of 'x' bauds/sec
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
	else if (baudrate == 115200){
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
}


