// 	*******************************************************************************************************************
//	NAME	       : P V S PHANEENDRA
// 	DESIGNATION    : GRADUATE ENGINEER TRAINEE
// 	COMPANY        : HITECH ROBOTIC SYSTEMZ LIMITED, GURGAON
// 	MODULE         : FUNCTIONS PROTOTYPES
//	VERSION	       : 1.0.3v	
// 	DATE OF DESIGN : 4th APRIL, 2010 
// 	DESIGN TOOLS   : KEIL uVISION v3.23a, FLASH MAGIC NXP's SERIAL PROGRAMMER, HYPERTERMINAL SOFTWARE - XCTU
// 	DESCRIPTION    : THIS FILE LISTS ALL THE FUCNTION PROTOTYPES REGARDING USE OF PERIPHERALS FOR NXP'S LPC2148
//					 FOR THE NGX's BLUEBOARD IN PARTICULAR.
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

#ifndef	_P_V_S_Phaneendra_H_
  #define _P_V_S_Phaneendra_H_
#endif


///////////////////////////////////////////////////////////////////////////////////////////////////////
// -------------------------------------- DELAY FUNCTION PROTOTYPE -----------------------------------
void setDelay (double);


///////////////////////////////////////////////////////////////////////////////////////////////////////
// ------------------------------------- BUZZER FUNCTION PROTOTYPE -----------------------------------
void playBuzzer (unsigned char);


////////////////////////////////////////////////////////////////////////////////////////////////////////
// ------------------------------ UART0 CONFIGURATION FUNCTION PROTOTYPE ------------------------------
void configureSerialUart0 (double, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char);

// ----------------------------------- UART0 TRANSMITTER PROTOTYPE ------------------------------------
void charTransmitFromUart0 (unsigned char);

// -------------------------------------- UART0 RECEIVE PROTOTYPE -------------------------------------
unsigned char charReceiveAtUart0 (void);

// -------------------------------------- FUNCTIONS USEFUL FOR DEBUGGING ------------------------------
void check (unsigned long int);


////////////////////////////////////////////////////////////////////////////////////////////////////////
// ------------------------------- 16x2 CHARACTER DISPLAY FUNCTIONS PROTOTYPES ------------------------
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
////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////// VECTOR INTERRUCT CONTROLLER (VIC) FUNCTIONS PROTOTYPES ////////////////////////////
void initVICInterruptSource (unsigned char);
void pinSelectInterruptSource (unsigned char);
void regVICInterruptSelect (unsigned char, unsigned char);
void regVICInterruptEnable (unsigned char);
void EXT_IRQ6 (void) __irq;
void EXT_IRQ16 (void) __irq;
