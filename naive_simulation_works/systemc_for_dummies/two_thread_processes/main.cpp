#include <systemc.h>
#include "Two_Thread_Processes.h"

int sc_main(int sc_argc, char* sc_argv[])
{
	Two_Thread_Processes Set_Processes("Set_Processes");
	
	sc_set_time_resolution(100, SC_PS);
	sc_start(10.0, SC_NS);

	return 0;
}
