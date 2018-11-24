#ifndef FULL_ADDER_H
#define FULL_ADDER_H

#include <systemc.h>
#include "Half_Adder.h"

SC_MODULE(Full_Adder)
{
	sc_in<bool> 	a, b, c_in;
	sc_out<bool>	sum_out, c_out;

	sc_signal<bool>	c1, c2, s1;

	Half_Adder *ha1_ptr, *ha2_ptr;

	void CstCalculateSum(void);

	SC_CTOR(Full_Adder)
	{
		ha1_ptr = new Half_Adder("ha1");
		// Named Associations
		ha1_ptr->a(a);
		ha1_ptr->b(b);
		ha1_ptr->carry(c1);
		ha1_ptr->sum(s1);
		
		ha2_ptr = new Half_Adder("ha2");
		// Positional Associations
		ha2_ptr->a(s1);
		ha2_ptr->b(c_in);
		ha2_ptr->carry(c2);
		ha2_ptr->sum(sum_out);
	
		SC_METHOD(CstCalculateSum);
			sensitive << c1 << c2;
	}

	~Full_Adder()
	{
		delete ha1_ptr;
		delete ha2_ptr;
	}
};

#endif	// End of FULL_ADDER_H
