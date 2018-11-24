#include "SampleScModule.h"

SampleScModule::SampleScModule(sc_module_name name)
: sc_module(name)
{
  std::cout << "\nConstructor called (implementation is in a separate file ...)\n" << std::endl;
}

SampleScModule::~SampleScModule()
{
}

