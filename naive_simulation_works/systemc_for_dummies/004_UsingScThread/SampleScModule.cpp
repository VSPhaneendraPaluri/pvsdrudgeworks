#include "SampleScModule.h"

SampleScModule::SampleScModule(sc_module_name name)
: sc_module(name)
, threadEventA("threadEventA")
, threadEventB("threadEventB")
, threadEventC("threadEventC")
, threadEventD("threadEventD")
{
  SC_THREAD(threadA);
    sensitive << threadEventA;

  SC_THREAD(threadB);
    sensitive << threadEventB;

  SC_THREAD(threadC);
    sensitive << threadEventC;

  SC_THREAD(threadD);
    sensitive << threadEventD;
}

SampleScModule::~SampleScModule()
{
}

void SampleScModule::threadA()
{
  cout << "Entered Thread A @" << sc_time_stamp() << endl;
  while(1)
  {
    cout << "Thread A  Waiting for Event A @" << sc_time_stamp() << endl;
    wait();
    cout << "Thread A  Resume after  Event A @" << sc_time_stamp() << endl;
    cout << "Notify Event B after 1 NS   @" << sc_time_stamp() << endl;
    threadEventB.notify(1, SC_NS);
    cout << "Pausing Thread A  for Event B @" << sc_time_stamp() << endl;
    wait(threadEventB);
    cout << "Resumed Thread A  after Event B @" << sc_time_stamp() << endl;
  }
}


void SampleScModule::threadB()
{
  cout << "Entered Thread B @" << sc_time_stamp() << endl;
  while(1)
  {
    cout << "Notify Event C after 1.5 NS   @" << sc_time_stamp() << endl;
    threadEventC.notify(1.5, SC_NS);
    cout << "Pausing Thread B  for Event B @" << sc_time_stamp() << endl;
    wait();
    cout << "Resumed Thread B  After Event B @" << sc_time_stamp() << endl;
  }
}


void SampleScModule::threadC()
{ 
  cout << "Entered Thread C @" << sc_time_stamp() << endl;
  cout << "Pausing Thread C  for Event C @" << sc_time_stamp() << endl;
  wait();
  cout << "Resumed Thread C  After Event C @" << sc_time_stamp() << endl;
  while(1)
  {
    cout << "Notify Event A after 0.5 NS   @" << sc_time_stamp() << endl;
    threadEventA.notify(0.5, SC_NS);
    cout << "Pausing Thread C for Event B and C  @" << sc_time_stamp() << endl;
    wait(threadEventB & threadEventC);
    cout << "Resumed Thread C  After Event B and C @" << sc_time_stamp() << endl;
    cout << "Notify Event D after xx  NS   @" << sc_time_stamp() << endl;
    threadEventD.notify();
    //cout << "Resumed Thread C @" << sc_time_stamp() << endl;
  }
}


void SampleScModule::threadD()
{
  cout << "Entered Thread D @" << sc_time_stamp() << endl;
  wait();
  cout << "Leaving Thread D @" << sc_time_stamp() << endl;
}

