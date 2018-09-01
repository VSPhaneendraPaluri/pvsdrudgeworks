#include <systemc.h>
#include "SystemC_Methods1.h"

int sc_main(int sc_argc, char* sc_argv[])
{
	SystemC_Methods1 myMethods1("myMethods1");

	sc_start(3.0, SC_NS);

	return 0;
}

