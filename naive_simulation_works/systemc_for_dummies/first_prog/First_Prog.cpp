#include<systemc.h>

SC_MODULE(SystemC_PVS)
{    
	SC_CTOR(SystemC_PVS)
	{
		SC_THREAD(main_thread);
	}

	void main_thread(void)
	{
		while(1)
		{
		        wait(10,SC_NS);
			SC_REPORT_INFO("Hello PVS!!","Welcome to SystemC!!");
			cout<<sc_time_stamp()<<endl;
			wait(SC_ZERO_TIME);
			cout << sc_time_stamp() << "\n";
		}
	}
};

int sc_main(int sc_argc, char* sc_argv[])
{
	SystemC_PVS SystemC_PVS_Object("");

	sc_start();

	return 0;
}

