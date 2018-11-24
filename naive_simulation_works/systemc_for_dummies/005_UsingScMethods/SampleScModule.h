#pragma once

#include <systemc.h>

class SampleScModule : public sc_module
{
  public:

    SC_HAS_PROCESS(SampleScModule);
    explicit SampleScModule(sc_module_name name);
    ~SampleScModule();

  private:

    sc_event methodEventA;
    sc_event methodEventB;
    sc_event methodEventC;
    sc_event methodEventD;

    void methodA(void);
    void methodB(void);
    void methodC(void);
    void methodD(void);
};

