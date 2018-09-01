#ifndef FOUR_BIT_ADDER_H
#define FOUR_BIT_ADDER_H

#include <systemc.h>
#include "Full_Adder.h"

SC_MODULE(Four_Bit_Adder)
{
	sc_in<sc_lv<1> >	a[4], b[4];
	sc_out<sc_lv<1> >	z[5];

	sc_signal<sc_lv<1> >	c0_in, c1_out, c2_out, c3_out;

	Full_Adder	*fa1_ptr, *fa2_ptr, *fa3_ptr, *fa4_ptr;
	
	int i;

	SC_CTOR(Four_Bit_Adder)
	{
		c0_in = '0';

		fa1_ptr	= new Full_Adder("FA1");
		fa1_ptr->a(a[0]);
		fa1_ptr->b(b[0]);
		fa1_ptr->c_in(c0_in);
		fa1_ptr->c_out(c1_out);
		fa1_ptr->sum_out(z[0]);

		fa2_ptr = new Full_Adder("FA2");
		fa2_ptr->a(a[1]);
		fa2_ptr->b(b[1]);
		fa2_ptr->c_in(c1_out);
		fa2_ptr->c_out(c2_out);
		fa2_ptr->sum_out(z[1]);

		fa3_ptr = new Full_Adder("FA3");
		fa3_ptr->a(a[2]);
		fa3_ptr->b(b[2]);
		fa3_ptr->c_in(c2_out);
		fa3_ptr->c_out(c3_out);
		fa3_ptr->sum_out(z[2]);

		fa4_ptr = new Full_Adder("FA4");
		fa4_ptr->a(a[3]);
		fa4_ptr->b(b[3]);
		fa4_ptr->c_in(c3_out);
		fa4_ptr->c_out(z[4]);
		fa4_ptr->sum_out(z[3]);
	}

	~Four_Bit_Adder()
	{
		cout << "Destructing..." << endl;
		delete fa1_ptr;
		delete fa2_ptr;
		delete fa3_ptr;
		delete fa4_ptr;
	}
};

#endif	// End of FOUR_BIT_ADDER_H
