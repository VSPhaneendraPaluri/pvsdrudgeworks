#include <avr/io.h>
#include <util/delay.h>

//#define	F_CPU 	16000000		// Oscillator Frequency (in Hz)

void USART_init(unsigned int);
void USART_transmit(unsigned char);

int main(void)
{
  	unsigned char var_a = 0, var_b = 0;

	// Enter the baudrate value {UBRRH:UBRRL} from the datasheet
  	unsigned int baudrate = 103;	// 12-bits can be set out of the 16-bits available 
									
	// Initialize the USART
	USART_init(baudrate);
	
	DDRB = 0xFF;	

  	while(1)
	{
		//Counter from 0 to 127
		for (var_a = 0;	var_a <= 127; var_a++)
		{
			PORTB	=	var_a;
			_delay_loop_2 (10000);
			USART_transmit (PORTB);
		}

		//Counter from 127 to 0
		for (var_b = var_a;	var_b >= 0; --var_b)
		{
			PORTB	=	var_b;
			_delay_loop_2 (10000);
			USART_transmit (PORTB);
		}

		//PORTB = 0x10;
		//USART_transmit (PORTB);
	}

  	return 0;
}

void USART_init(unsigned int baudrate)
{
    // Setting baud rate 
	UBRRH	|= 	(0 << URSEL);
	UBRRH 	 =	(unsigned char)(baudrate >> 8);
	UBRRL 	 =	(unsigned char)baudrate;
	
	// Enable the transmitter and receiver
	UCSRB |= (1 << RXEN) | (1 << TXEN);	
}

void USART_transmit (unsigned char var_a)
{
	
	// Setting the parameters for USART transmission
	while (!(UCSRA & (1 << UDRE)));

	UDR = var_a;
}
