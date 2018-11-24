#include "SampleScModule.h"

int sc_main(int sc_argc, char* sc_argv[])
{
  SampleScModule sampleModule("SampleScModule");

  sc_start(3.0, SC_NS);

  return 0;
}

