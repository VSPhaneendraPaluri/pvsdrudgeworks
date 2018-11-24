#pragma once
#include <systemc.h>

SC_MODULE(SampleScModule)
{
  public:
    
    SC_CTOR(SampleScModule)
    {
      std::cout << "\nSC_CTOR has been called ...\n" << std::endl;
    }
};

