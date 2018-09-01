#ifndef HALF_ADDER_H
#define HALF_ADDER_H

#include <systemc.h>

SC_MODULE(Half_Adder)
{
	// Ports for Half Adder
	sc_in<sc_lv<1> >	a, b;
	sc_out<sc_lv<1> >	sum, carry;
	
	void HA_Process_Inputs();

	SC_CTOR(Half_Adder)
	{
		SC_METHOD(HA_Process_Inputs);
		sensitive << a << b;
	}
};

#endif // End of HALF_ADDER_H
