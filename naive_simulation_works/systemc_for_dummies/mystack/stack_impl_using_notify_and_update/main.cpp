#include <systemc.h>
#include "MyTestBenchDriver.h"
#include "MyTestBenchMonitor.h"
#include "Stack1_Master.h"
#include "Stack1_Slave.h"
#include "Stack1_Channel.h"

using namespace sc_core;

int sc_main(int sc_argc, char* sc_argv[])
{
	sc_signal<int> Msignal, Ssignal;
	
	MyTestBenchDriver	Driver("Driver");
	Stack1_Master		Master("Master");
	Stack1_Slave		Slave("Slave");
	Stack1_Channel 		Channel("channel");
	MyTestBenchMonitor	Monitor("Monitor");

	Driver.TBD_a(Msignal);
	Master.In_Port(Msignal);

	Master.Master_Port(Channel);
	Slave.Slave_Port(Channel);
	
	Slave.Out_Port(Ssignal);
	Monitor.TBM_M(Msignal);
	Monitor.TBM_S(Ssignal);

	sc_set_time_resolution(1, SC_NS);
	
	sc_start(100.0, SC_NS);

	return 0;
}
