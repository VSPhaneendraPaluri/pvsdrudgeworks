#include <systemc.h>
#include "SystemC_Methods1.h"

void SystemC_Methods1::A_Method()
{
	cout << "Method A waiting for Event A @" << sc_time_stamp() << endl;
	cout << "Immediate notification of Event B in Method A @" << sc_time_stamp() << endl;
	b_method_event.notify();
	cout << "Changing the static sensitivity of Method A to Event C @" << sc_time_stamp() << endl;
	next_trigger(c_method_event);
	cout << "Method A notifying Event C in 1.5 NS from" << sc_time_stamp() << endl;
	c_method_event.notify(1.5, SC_NS);
	cout << "Exiting Method A @" << sc_time_stamp() << endl;
}


void SystemC_Methods1::B_Method()
{
	cout << "Method B waiting for Event B @" << sc_time_stamp() << endl;
	cout << "Method B notify Event A in 0 NS from" << sc_time_stamp() << endl;
	a_method_event.notify(SC_ZERO_TIME);
	cout << "Method B exiting @" << sc_time_stamp() << endl;		
}


void SystemC_Methods1::C_Method()
{
	cout << "Method C waiting for Event C @" << sc_time_stamp() << endl;
	next_trigger(a_method_event);
	cout << "Changed static sensitivity for Method C to Event A @" << sc_time_stamp() << endl;
	cout << "Exiting Method C @" << sc_time_stamp() << endl;
}


void SystemC_Methods1::D_Method()
{

}
