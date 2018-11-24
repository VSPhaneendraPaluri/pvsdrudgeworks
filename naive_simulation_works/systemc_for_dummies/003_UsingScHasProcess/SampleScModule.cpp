#include "SampleScModule.h"

SampleScModule::SampleScModule(sc_module_name name)
: sc_module(name)
{
  std::cout << "\nDemonstrating SC_HAS_PROCESS ...\n" << std::endl;

  SC_METHOD(ScMethodCall);

  SC_THREAD(ScThreadCall);
}

SampleScModule::~SampleScModule()
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void SampleScModule::ScMethodCall()
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void SampleScModule::ScThreadCall()
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

