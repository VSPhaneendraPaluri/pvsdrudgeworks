#include <systemc.h>
#include "SystemC_Threads1.h"

int sc_main(int sc_argc, char* sc_argv[])
{
	SystemC_Threads1 myThreads1("myThreads1");

	sc_start(10.0, SC_NS);

	return 0;
}

