#include <LPC214x.H>
#include "P_V_S_Phaneendra.h" 


// ------------------- I2C0 Port Communication Lines ------------------------
#define 	SCL0	(1 << 4)		//Serial Clock Line
#define		SDA0	(1 << 6)		//Serial Data Address

// -------------------------- READ-WRITE SYMBOLS ----------------------------
#define 	DEV_ADD		0x50
#define 	READ_MASK	0xFF
#define		WRITE_MASK	0xFE

// ----------------------------- I2C FLAGS ----------------------------------
#define		I2C_ENABLE_FLAG		6
#define 	I2C_START_FLAG		5
#define		I2C_STOP_FLAG		4
#define		I2C_INTERRUPT_FLAG	3
#define		I2C_ACK_FLAG		2


void configureSerialUart0 (double, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char);
void charTransmitFromUart0 (unsigned char);

void selectI2CCommunicationProtocol (unsigned char);
void setI2CBaudRate	(unsigned char, unsigned char);
void modeSelectI2CCommunicationProtocol (unsigned char);
void I2CCommunicationWriteByte (unsigned int, unsigned char);
void I2CCommunicationReadByte (unsigned int);

int main (void)
{
	unsigned char I2CPortSelect		= 	0;
	unsigned char serialClockLow	=	0x50;
	unsigned char serialClockHigh	=	0x50;
	unsigned char modeSelectByte	=	0;

	configureSerialUart0 (9600, 0, 0, 0, 1, 3);
	
	selectI2CCommunicationProtocol(I2CPortSelect);
	setI2CBaudRate (serialClockLow, serialClockHigh);
	modeSelectI2CCommunicationProtocol (modeSelectByte);
	I2CCommunicationWriteByte (0x0000, 0x10);
	I2CCommunicationWriteByte (0x0001, 0x20);
	I2CCommunicationWriteByte (0x0002, 0x30);
	I2CCommunicationReadByte (0x0001);

	return 0;
}


void selectI2CCommunicationProtocol (unsigned char I2CPortSelect)
{
	if(!I2CPortSelect)
	{
		PINSEL0	|=	(SCL0)|(SDA0);	   	// Port 0 Pin 22 -> SCL0 and Pin 26 -> SDA0
	} 
	VPBDIV	=	0x2;					//PCLK	=	32.768 MHz =>  VPBCLK !=  30 MHz  => Set VPBCLK	= CCLK = 60 MHz
}


void setI2CBaudRate	(unsigned char serialClockLow, unsigned char serialClockHigh)
{
 	I2C0SCLL	=	serialClockLow;
	I2C0SCLH	=	serialClockHigh;
}


void modeSelectI2CCommunicationProtocol (unsigned char modeSelectByte)
{
	I2C0CONCLR	|=	0x6C;						//  Clear the I2C Interrupt flags
	I2C0CONSET	=	(1 << I2C_ENABLE_FLAG);		// 	Enable I2C0 port for I2C Communication	

	switch (modeSelectByte)
	{
		// Initialize I2C0CONSET before entering Master Transmit Mode
		case 0:	{	
					I2C0CONSET	=	(0 << I2C_START_FLAG)|(0 << I2C_STOP_FLAG)|(0 << I2C_INTERRUPT_FLAG)|(0 << I2C_ACK_FLAG); 
					break;
				}
	
		// Initialize I2C0CONSET before entering Master Receive Mode
		case 1:	{	
					I2C0CONSET	=	(0 << I2C_START_FLAG)|(0 << I2C_STOP_FLAG)|(0 << I2C_INTERRUPT_FLAG)|(0 << I2C_ACK_FLAG);
					break;
				}
		
		// Initialize I2C0CONSET before entering Slave Transmit Mode
		case 2:	{	
					I2C0CONSET	=	(0 << I2C_START_FLAG)|(0 << I2C_STOP_FLAG)|(0 << I2C_INTERRUPT_FLAG)|(1 << I2C_ACK_FLAG);
					break;
				}

		// Initialize I2C0CONSET before entering Slave Receive Mode
		case 3:	{	
					I2C0CONSET	=	(0 << I2C_START_FLAG)|(0 << I2C_STOP_FLAG)|(0 << I2C_INTERRUPT_FLAG)|(1 << I2C_ACK_FLAG);
					break;
				}
	}
}


void I2CCommunicationWriteByte (unsigned int address, unsigned char data)
{
	// -------------------------------------- Code for Signalling Start Condition ---------------------------------------
	I2C0CONSET	|=	(1 << I2C_START_FLAG);				//	Set the flag to start I2C Communication
	while (!(I2C0CONSET & (1 << I2C_INTERRUPT_FLAG)));	// 	Wait for the I2C Bus State to change indicating that the
														// 	start condition has been transmitted
	
	if((I2C0STAT == 0x08))							   	//	Display status data contained within I2C0STAT Register
		charTransmitFromUart0 (I2C0STAT);			 

	I2C0CONCLR	|=	(1 << I2C_START_FLAG)|(1 << I2C_INTERRUPT_FLAG); 	//	Clear the Start bit and the Interrupt flag	
	
	// ----------------------------------- Transmit the control byte, i.e., Device ID ---------------------------------------
	I2C0DAT		=	(DEV_ADD << 1) && WRITE_MASK;		//	A0 and A1 are 0's (pulled low) hence, Device ID = 1-0-1-0-0-A1-A0
	while (!(I2C0CONSET & (1 << I2C_INTERRUPT_FLAG)));	// 	Wait for the I2C Bus State to change indicating that the
														//	Device ID has been transmitted
	
	if((I2C0STAT == 0x18))						   		//	Display status data contained within I2C0STAT Register
		charTransmitFromUart0 (I2C0STAT);
			
	I2C0CONCLR	=	(1 << I2C_INTERRUPT_FLAG);			//	Clear the Interrupt flag
	
	// ----------------------------- Transmit the Address bytes (first Higher and then Lower byte) --------------------------
	I2C0DAT		=	(address >> 8);								//	8-bits representing the Address Bytes (1st Higher Byte, 2nd Lower Byte)
	while (!(I2C0CONSET & (1 << I2C_INTERRUPT_FLAG)));	// 	Wait for the I2C Bus State to change indicating that the
														//	Higher Address Byte has been transmitted
	
	if((I2C0STAT == 0x28))						   		//	Display status data contained within I2C0STAT Register
		charTransmitFromUart0 (I2C0STAT);			
	
	I2C0CONCLR	=	(1 << I2C_INTERRUPT_FLAG);			//	Clear the Interrupt flag
	
	I2C0DAT		=	address;								//	8-bits representing the Address Bytes (1st Higher Byte, 2nd Lower Byte)
	while (!(I2C0CONSET & (1 << I2C_INTERRUPT_FLAG)));	// 	Wait for the I2C Bus State to change indicating that the
														//	Lower Address Byte has been transmitted
	
	if((I2C0STAT == 0x28))						   		//	Display status data contained within I2C0STAT Register
		charTransmitFromUart0 (I2C0STAT);			
	
	I2C0CONCLR	=	(1 << I2C_INTERRUPT_FLAG);			//	Clear the Interrupt flag

	// ----------------------------------------- Transmit the Data bytes ----------------------------------------------
	I2C0DAT		=	data;								//	8-bits representing the Data Byte
	while (!(I2C0CONSET & (1 << I2C_INTERRUPT_FLAG)));	// 	Wait for the I2C Bus State to change indicating that the
														//	Data Byte has been transmitted
	
	if((I2C0STAT == 0x28))						   		//	Display status data contained within I2C0STAT Register
		charTransmitFromUart0 (I2C0STAT);
			
	I2C0CONCLR	=	(1 << I2C_INTERRUPT_FLAG);			//	Clear the Interrupt flag

	// -------------------------------------------- Transmit the Stop Bit -----------------------------------------
	I2C0CONSET	|=	(1 << I2C_STOP_FLAG);
}


void I2CCommunicationReadByte (unsigned int address)
{
	unsigned char	receivedData;		

	// -------------------------------------- Code for Signalling Start Condition ---------------------------------------
	I2C0CONSET	|=	(1 << I2C_START_FLAG);				//	Set the flag to start I2C Communication
	while (!(I2C0CONSET & (1 << I2C_INTERRUPT_FLAG)));	// 	Wait for the I2C Bus State to change indicating that the
														// 	start condition has been transmitted
	
	if((I2C0STAT == 0x08))							   	//	Display status data contained within I2C0STAT Register
		charTransmitFromUart0 (I2C0STAT);			 

	I2C0CONCLR	|=	(1 << I2C_START_FLAG)|(1 << I2C_INTERRUPT_FLAG); 	//	Clear the Start bit and the Interrupt flag	
	
	// ----------------------------------- Transmit the control byte, i.e., Device ID ---------------------------------------
	I2C0DAT		=	(DEV_ADD << 1) && READ_MASK;		//	A0 and A1 are 0's (pulled low) hence, Device ID = 1-0-1-0-0-A1-A0
	while (!(I2C0CONSET & (1 << I2C_INTERRUPT_FLAG)));	// 	Wait for the I2C Bus State to change indicating that the
														//	Device ID has been transmitted
	
	if((I2C0STAT == 0x40))						   		//	Display status data contained within I2C0STAT Register
		charTransmitFromUart0 (I2C0STAT);			
	
	I2C0CONCLR	=	(1 << I2C_INTERRUPT_FLAG);			//	Clear the Interrupt flag
	
	// ----------------------------- Transmit the Address bytes (first Higher and then Lower byte) --------------------------
	I2C0DAT		=	(address >> 8);								//	8-bits representing the Address Bytes (1st Higher Byte, 2nd Lower Byte)
	while (!(I2C0CONSET & (1 << I2C_INTERRUPT_FLAG)));	// 	Wait for the I2C Bus State to change indicating that the
														//	Higher Address Byte has been transmitted
	
	if((I2C0STAT == 0x28))						   		//	Display status data contained within I2C0STAT Register
		charTransmitFromUart0 (I2C0STAT);			
	
	I2C0CONCLR	=	(1 << I2C_INTERRUPT_FLAG);			//	Clear the Interrupt flag
	
	I2C0DAT		=	address;								//	8-bits representing the Address Bytes (1st Higher Byte, 2nd Lower Byte)
	while (!(I2C0CONSET & (1 << I2C_INTERRUPT_FLAG)));	// 	Wait for the I2C Bus State to change indicating that the
														//	Lower Address Byte has been transmitted
	
	if((I2C0STAT == 0x28))						   		//	Display status data contained within I2C0STAT Register
		charTransmitFromUart0 (I2C0STAT);			
	
	I2C0CONCLR	=	(1 << I2C_INTERRUPT_FLAG);			//	Clear the Interrupt flag

	// -------------------------------------------- Receive the Data bytes  -------------------------------------------------
	receivedData	=	I2C0DAT	;						//	8-bits representing the Data Byte
	while (!(I2C0CONSET & (1 << I2C_INTERRUPT_FLAG)));	// 	Wait for the I2C Bus State to change indicating that the
														//	Data Byte has been transmitted
	
	if((I2C0STAT == 0x50))						   		//	Display status data contained within I2C0STAT Register
		charTransmitFromUart0 (receivedData);			
		charTransmitFromUart0 (I2C0STAT);
		
	I2C0CONCLR	=	(1 << I2C_INTERRUPT_FLAG);			//	Clear the Interrupt flag

	// -------------------------------------------- Transmit the Stop Bit -----------------------------------------
	I2C0CONSET	|=	(1 << I2C_STOP_FLAG);
}
