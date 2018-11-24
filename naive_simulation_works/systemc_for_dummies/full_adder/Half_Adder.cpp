#include "Half_Adder.h"

void Half_Adder::HA_Process_Inputs()
{
	sum.write(a.read() ^ b.read());
	carry	=	a.read() & b.read();
}
