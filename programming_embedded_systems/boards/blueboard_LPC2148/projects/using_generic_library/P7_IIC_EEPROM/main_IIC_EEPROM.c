#include <lpc214x.h>
#include "P_V_S_Phaneendra.h"

#define SCL0	(1 << 4)	//00010000
#define SDA0	(1 << 6)	//01000000

#define SCL0_RESET	(3 << 4)
#define SDA0_RESET	(3 << 6)	

#define IIC_ENABLE	(1 << 6)
#define IIC_START	(1 << 5)
#define IIC_STOP	(1 << 4)
#define IIC_ACK		(1 << 3)
#define IIC_MS	    (1 << 2)

#ifndef NULL
	#define NULL 0
#endif

void IIC0_PinSelectFunction(void);
void IIC0_SetI2CCommSpeed(void);
void IIC0_EnableAndStart(void);
void IIC0_Restart(void);
void IIC0_SlaveAddress(void);
void IIC0_SetAddress(unsigned int);
void IIC0_Stop(void);

void IIC0_PinSelectFunction(void)
{
	PINSEL0	|=	(PINSEL0 & ~SCL0_RESET)|(SCL0);
	PINSEL0	|=	(PINSEL0 & ~SDA0_RESET)|(SDA0);
}

void IIC0_SetI2CCommSpeed (void)
{
	// Set up the speed registers of the I2C0 protocol
	// SCLH + SCLL = (15MHz/100KHz) = 150
	I2C0SCLH	=	75;
	I2C0SCLL	=	75;
}

void IIC0_EnableAndStart(void)
{
	I2C0CONCLR	=	0x7C;						//	Clear All Interrupts
	I2C0CONSET  =   IIC_MS;
	I2C0CONSET	=	IIC_ENABLE | IIC_START;			 		//	Enable I2C
	charTransmitFromUart0(I2C0STAT);
	charTransmitFromUart0(0x0D);
}

void IIC0_Restart(void)
{
	I2C0CONCLR	=	IIC_ACK;			//	Clear "SI Flag" or IIC_ACK	
	I2C0CONSET	=	IIC_START;			//	STA bit set high
	while(!(I2C0CONSET & IIC_ACK));		//	Wait while the acknowledge bit is set 
	charTransmitFromUart0(I2C0STAT);
}

void IIC0_SlaveAddress(void)
{
	//	Set this slave ID to write to EEPROM
	I2C0DAT		=	0xA0;		//	1-0-1-0-A2-A1-A0-(R/~W)	=> 0x10100000
	I2C0CONSET  =   IIC_MS;
	I2C0CONCLR	=	IIC_ACK;
	while(!(I2C0CONSET & IIC_ACK));
	charTransmitFromUart0(I2C0STAT);
	charTransmitFromUart0(0x0D);
}

void IIC0_SetAddress (unsigned int address)
{
	// Set the memory addresses to be written to
	// Starting Address = 0x0000; Final Address = 0x7FFF
	I2C0DAT		=	(address >> 8);
	I2C0CONSET  =   IIC_MS;
	I2C0CONCLR	=	IIC_ACK;
	while(!(I2C0CONSET & IIC_ACK));
	charTransmitFromUart0 (I2C0STAT);
	
	I2C0DAT		=	address;
	I2C0CONSET  =   IIC_MS;
	I2C0CONCLR	=	IIC_ACK;
	while(!(I2C0CONSET & IIC_ACK));
	charTransmitFromUart0 (I2C0STAT);
	charTransmitFromUart0 (0x0D);
}

void IIC0_Stop(void)
{
	I2C0CONCLR	=	IIC_ACK;			//	Clear "SI Flag"
	I2C0CONSET	=	IIC_STOP|IIC_MS;	//  Set Start bit high and Enable I2C device to get slave mode		
	charTransmitFromUart0(I2C0STAT);
}

int main (void)
{
	unsigned int i = 0;
	unsigned char rb;
	unsigned int address = 0x0000;
	char buffer[17]	=	"P V S Phaneendra";

	// Set up the configuration parameters for the UART0
	configureSerialUart0 (38400, 0, 0, 0, 1, 8);

	rb	=	charReceiveAtUart0 ();
	charTransmitFromUart0 (rb);

	IIC0_PinSelectFunction();
	IIC0_SetI2CCommSpeed();
	IIC0_EnableAndStart();
	IIC0_SlaveAddress();
	IIC0_SetAddress(address);	

	while(buffer[i] != NULL)
	{
		I2C0DAT	=	buffer[i];
		I2C0CONCLR	=	IIC_ACK;
		while(!(I2C0CONSET & IIC_ACK));
		charTransmitFromUart0 (buffer[i]);
		charTransmitFromUart0 (I2C0STAT);
		charTransmitFromUart0 (0x0D);
		i++;
	}

	IIC0_Stop();
}
