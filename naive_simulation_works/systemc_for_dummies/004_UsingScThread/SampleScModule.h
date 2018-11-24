#pragma once

#include <systemc.h>

class SampleScModule : public sc_module
{
  public:

    SC_HAS_PROCESS(SampleScModule);
    explicit SampleScModule(sc_module_name name);
    ~SampleScModule();

  private:

    sc_event threadEventA;
    sc_event threadEventB;
    sc_event threadEventC;
    sc_event threadEventD;

    void threadA(void);
    void threadB(void);
    void threadC(void);
    void threadD(void);
};

