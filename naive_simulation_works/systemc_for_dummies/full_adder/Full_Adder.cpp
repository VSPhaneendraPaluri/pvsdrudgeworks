#include "Full_Adder.h"

void Full_Adder::CstCalculateSum()
{
	c_out	=	c1.read() | c2.read();
}
