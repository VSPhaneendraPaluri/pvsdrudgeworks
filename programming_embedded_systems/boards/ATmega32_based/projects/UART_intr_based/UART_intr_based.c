#include <avr/io.h>
#include <util/delay.h>

//#define F_CPU	16000000

void UART_config (unsigned char);
unsigned char UART_receive();
void UART_transmit (unsigned char);


int main ()
{
	unsigned char baudrate = 103;	
	unsigned char data=0;
	unsigned char data1 = 0;

	UART_config(baudrate);

	while (1)
	{
		data	= 	UART_receive();
		UART_transmit(data);
		_delay_ms(200);
	}

	return 0;
}


void UART_config (unsigned char baudrate)
{
	//UBRRH	|=	(0 << URSEL);
	UBRRH	=	(unsigned char)(baudrate >> 8);
	UBRRL	=	(unsigned char)baudrate;

	UCSRA	|=	(1 << UDRE);
	
	UCSRB	= 	(1 << RXEN)|(1 << TXEN);
	UCSRC	= 	(1 << URSEL)|(0 << UMSEL)|(1 << UCSZ0)|(1 << UCSZ1);
} 

void UART_transmit (unsigned char vara)
{
	while (!(UCSRA & (1 << UDRE)));
	UDR	= vara;
}

unsigned char UART_receive()
{
	unsigned char ch;
	while (!(UCSRA & (1 << RXC)));
	ch=UDR;
	return ch;
}



