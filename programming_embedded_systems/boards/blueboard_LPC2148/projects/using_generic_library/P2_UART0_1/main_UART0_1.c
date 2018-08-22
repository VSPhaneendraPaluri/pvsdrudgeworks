#include "P_V_S_Phaneendra.h"

void playBuzzer (unsigned char, double);
void configureSerialUart0 (double, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char);
void charTransmitFromUart0 (unsigned char);
unsigned char charReceiveAtUart0 (void);

int main(void)
{
	unsigned char data;
	unsigned char setbreak = 0;
	unsigned char parity = 0;
	unsigned char N = 1;
	unsigned char stopbits = 1;
	unsigned char wordlen = 8;
	double baudrate = 9600;
	
	configureSerialUart0 (baudrate, setbreak, parity, N, stopbits, wordlen);
	
	while(1)
	{
		for(data = 0; data <= 127; data++)
			charTransmitFromUart0 (data);
		data = charReceiveAtUart0 ();
		charTransmitFromUart0 (data);
		playBuzzer (0,10000);
		playBuzzer (1,10000);
	}
}
