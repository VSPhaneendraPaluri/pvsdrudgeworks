// 	******************************************************************************************************************
//	NAME		   : P V S PHANEENDRA
// 	DESIGNATION    : GRADUATE ENGINEER TRAINEE
// 	COMPANY        : HITECH ROBOTIC SYSTEMZ LIMITED, GURGAON
// 	MODULE         : FUNCTIONS PROTOTYPES
//	VERSION		   : 1.0.0v	
// 	DATE OF DESIGN : 11th MARCH, 2010 
// 	DESIGN TOOLS   : KEIL uVISION v3.23a, FLASH MAGIC NXP's SERIAL PROGRAMMER, HYPERTERMINAL SOFTWARE - XCTU
// 	DESCRIPTION    : THIS FILE LISTS ALL THE FUCNTION PROTOTYPES REGARDING USE OF PERIPHERALS FOR NXP'S LPC2148
//					 FOR THE NGX's BLUEBOARD IN PARTICULAR.
// 	LICENSE        : ANYONE IS TO COPY, USE OR PUBLISH THIS MODULE AS LONG AS THE HEADER OF THIS MODULE IS NOT REMOVED.
// *******************************************************************************************************************

#ifndef _P_V_S_PHANEENDRA_H_
	#define _P_V_S_PHANEENDRA_H_
#endif

#include <LPC214x.h>

// -------------------------------------- DELAY FUNCTION PROTOTYPE -----------------------------------
void setDelay (double);

// ------------------------------------- BUZZER FUNCTION PROTOTYPE -----------------------------------
void playBuzzer (unsigned char, double);

// ------------------------------ UART0 CONFIGURATION FUNCTION PROTOTYPE ------------------------------
void configureSerialUart0 (double, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char);

// ----------------------------------- UART0 TRANSMITTER PROTOTYPE ------------------------------------
void charTransmitFromUart0 (unsigned char);

// -------------------------------------- UART0 RECEIVE PROTOTYPE -------------------------------------
unsigned char charReceiveAtUart0 (void);
