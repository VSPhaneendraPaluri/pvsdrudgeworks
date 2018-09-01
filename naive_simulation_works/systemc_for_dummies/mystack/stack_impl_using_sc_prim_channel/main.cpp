#include <systemc.h>
#include "Stack1_Master.h"
#include "Stack1_Slave.h"
#include "Stack1_Channel.h"

int sc_main(int sc_argc, char* sc_argv[])
{
	sc_signal<int> Msignal, Ssignal;
	
	Stack1_Master		Master("Master");
	Stack1_Slave		Slave("Slave");
	Stack1_Channel 		Channel;

	Master.Master_Port(Channel);
	Slave.Slave_Port(Channel);
	
	sc_set_time_resolution(1, SC_NS);
	
	sc_start(10.0, SC_NS);

	return 0;
}
