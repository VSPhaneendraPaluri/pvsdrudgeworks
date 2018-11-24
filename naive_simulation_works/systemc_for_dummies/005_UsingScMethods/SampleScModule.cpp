#include "SampleScModule.h"

SampleScModule::SampleScModule(sc_module_name name)
: sc_module(name)
, methodEventA("methodEventA")
, methodEventB("methodEventB")
, methodEventC("methodEventC")
, methodEventD("methodEventD")
{
  std::cout << "\nDemonstrating use of SC_METHOD ..." << std::endl;

  SC_METHOD(methodA);
    sensitive << methodEventA;

  SC_METHOD(methodB);
    sensitive << methodEventB;

  SC_METHOD(methodC);
    sensitive << methodEventC;

  SC_METHOD(methodD);
    sensitive << methodEventD;
}

SampleScModule::~SampleScModule()
{
}

void SampleScModule::methodA()
{
  cout << "Method A waiting for Event A @" << sc_time_stamp() << endl;
  cout << "Immediate notification of Event B in Method A @" << sc_time_stamp() << endl;
  methodEventB.notify();
  cout << "Changing the static sensitivity of Method A to Event C @" << sc_time_stamp() << endl;
  next_trigger(methodEventC);
  cout << "Method A notifying Event C in 1.5 NS from" << sc_time_stamp() << endl;
  methodEventC.notify(1.5, SC_NS);
  cout << "Exiting Method A @" << sc_time_stamp() << endl;
}


void SampleScModule::methodB()
{
  cout << "Method B waiting for Event B @" << sc_time_stamp() << endl;
  cout << "Method B notify Event A in 0 NS from" << sc_time_stamp() << endl;
  methodEventA.notify(SC_ZERO_TIME);
  cout << "Method B exiting @" << sc_time_stamp() << endl;  
}


void SampleScModule::methodC()
{
  cout << "Method C waiting for Event C @" << sc_time_stamp() << endl;
  next_trigger(methodEventA);
  cout << "Changed static sensitivity for Method C to Event A @" << sc_time_stamp() << endl;
  cout << "Exiting Method C @" << sc_time_stamp() << endl;
}


void SampleScModule::methodD()
{
}
