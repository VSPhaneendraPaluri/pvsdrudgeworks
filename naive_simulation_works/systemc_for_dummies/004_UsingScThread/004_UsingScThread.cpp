#include "SampleScModule.h"
#include <systemc.h>

int sc_main(int sc_argc, char* sc_argv[])
{
  SampleScModule sampleScModule("SampleScModule");
  
  sc_start(10.0, SC_NS);

  return 0;
}

