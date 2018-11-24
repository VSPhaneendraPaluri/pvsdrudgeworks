#include <systemc.h>
#include "Four_Bit_Adder.h"
#include "MyTestBenchDriver.h"
#include "MyTestBenchMonitor.h"

int sc_main(int sc_argc, char* sc_argv[])
{
	sc_signal<sc_lv<1> > pb_a[4], pb_b[4], pb_z[5];

	int	i = 0;

	Four_Bit_Adder MyAdder("MyAdder");
	for(i=0; i < 4; i++)
	{
		MyAdder.a[i](pb_a[i]);
		MyAdder.b[i](pb_b[i]);
		MyAdder.z[i](pb_z[i]);
		cout << "Instantiated MyAdder : " << i << endl;
	}
	MyAdder.z[4](pb_z[4]);

	MyTestBenchDriver MyTBDriver("MyTBDriver");
	for(i=0; i < 4; i++)
	{
		
		MyTBDriver.TBD_a[i](pb_a[i]);
		MyTBDriver.TBD_b[i](pb_b[i]);
		cout << "Instantiated MyTestBenchDriver : " << i << endl;
	}

	MyTestBenchMonitor MyTBMonitor("MyTBMonitor");
	for(i=0; i < 4; i++)
	{
		MyTBMonitor.TBM_a[i](pb_a[i]);
		MyTBMonitor.TBM_b[i](pb_b[i]);
		MyTBMonitor.TBM_z[i](pb_z[i]);
		cout << "Instantiated MyTestBenchMonitor : " << i << endl;
	}
	MyTBMonitor.TBM_z[4](pb_z[4]);
	
	sc_set_time_resolution(1, SC_NS);
	sc_start(60.0, SC_NS);

	return 0;
}
