#ifndef SYSTEMC_METHODS1_H
#define SYSTEMC_METHODS1_H

#include <systemc.h>

SC_MODULE (SystemC_Methods1)
{
	sc_event a_method_event, b_method_event, c_method_event, d_method_event;
	
	void A_Method(void);
	void B_Method(void);
	void C_Method(void);
	void D_Method(void);

	SC_CTOR (SystemC_Methods1)
	{
		SC_METHOD(A_Method);
			sensitive << a_method_event;
			cout << "Initialized Method A" << endl;

		SC_METHOD(B_Method);
			sensitive << b_method_event;
			dont_initialize();
			cout << "Not Initialized Method B" << endl;
		
		SC_METHOD(C_Method);
			sensitive << c_method_event;
			cout << "Initialized Method C" << endl;

		SC_METHOD(D_Method);
			sensitive << d_method_event;
			cout << "Initialized Method D" << endl;
	}
};

#endif // End of SYSTEMC_METHODS1_H
