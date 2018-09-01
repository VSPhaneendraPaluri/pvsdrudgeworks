#include <systemc.h>
#include "Half_Adder.h"

void Half_Adder::HA_Process_Inputs()
{
	sum	=	a^b;
	carry	=	a&b;
}
