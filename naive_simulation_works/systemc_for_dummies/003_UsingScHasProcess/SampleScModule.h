#pragma once
#include <systemc.h>

class SampleScModule : public sc_module
{
  public :

    SC_HAS_PROCESS(SampleScModule);

    explicit SampleScModule(sc_module_name name);
    ~SampleScModule();

  private :
    void ScMethodCall();
    void ScThreadCall();
};

