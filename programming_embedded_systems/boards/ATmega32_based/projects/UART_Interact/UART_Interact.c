#include <avr/io.h>
#include <avr/interrupt.h>

#define BUFFERSIZ	80		// Length of buffer 

void UART_config(unsigned char,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char);
unsigned char UART_receive();
unsigned char UART_interactmode(unsigned char);
void UART_transmit(unsigned char);

unsigned char *chPtr, data[BUFFERSIZ];

int main()
{
	unsigned char baudrate  =	103;	// See the table for Fosc = 16000000
	unsigned char synchoprt	=	0;		// Async = 0; Sync = 1;
	unsigned char parity	= 	0;		// No Parity = 0; Even Parity = 2; Odd Parity = 3;
	unsigned char stopbits	=	0;		// 1 Stop Bit = 0; 2 Stop Bits = 1;
	unsigned char charsize	= 	8;		// 5Bit = 0; 6Bit = 1; 7Bit = 2; 8Bit = 3; 9Bit = 7;	
	unsigned char polarity	= 	0;		// RisingTx = 0; RisingRx = 1;
		
	unsigned char identifymode, setmode;

	UART_config(baudrate, synchoprt, parity, stopbits, charsize, polarity);
	
	chPtr = data;
	identifymode = UART_receive();
	setmode = UART_interactmode(identifymode);

	while(1)
	{
		UART_transmit(setmode);
	}	

	return 0;
}

void UART_config(unsigned char baudrate,unsigned char synchoprt,unsigned char parity,unsigned char stopbits,unsigned char charsize,unsigned char polarity)
{
	unsigned char MSB;
	
	UBRRH	=	(unsigned char)(baudrate >> 8);
	UBRRL	=	(unsigned char)baudrate;
	
	UCSRA	|=	(1	<< UDRE);
	
	if (charsize <= 8)
	{
		MSB = 0; 
		charsize -= 5;
	} 
	else 
	{
		MSB = 1; 
		charsize -= 6;
	}

	UCSRB	|=	(1	<< RXEN)|(1	<< TXEN)|(MSB << UCSZ2);
	
	UCSRC	|=	(1	<< URSEL)|(synchoprt << UMSEL)|(parity << UPM0)|(stopbits << USBS)|(charsize <<	UCSZ0);	

}

unsigned char UART_receive()
{
	unsigned char capturedat;

	while(!(UCSRA & (1 << RXC)));
	capturedat = UDR;

	return capturedat;
}

unsigned char UART_interactmode(unsigned char identifymode)
{
	unsigned char retVal;

	if((identifymode == 87)|(identifymode == 119))
		retVal = 0x00;
	else if((identifymode == 83)|(identifymode == 115))
		 retVal = 0x01;

	return retVal;
}		

void UART_transmit(unsigned char setmode)
{
	unsigned char ch;
	
	if(setmode == 0)
	{
		ch = UART_receive();
		while(!(UCSRA & (1 << UDRE)));
		UDR = ch;
	}
	else if(setmode == 1)
	{	
		ch = UART_receive();
		if(ch != 0x0D)
		{	
			*(chPtr) = ch;
			chPtr++;			
		}
		else if(ch == 0x0D)
		{
			*(chPtr) = ch;
			chPtr = data;
			while(*(chPtr) != 0x0D)
			{
				while(!(UCSRA & (1 << UDRE)));
				UDR = *(chPtr++);
			}

		}	
		
	}
}

