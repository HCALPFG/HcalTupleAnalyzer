#include "HcalSample.h"

HcalSample::HcalSample():
  Object()
{}

HcalSample::HcalSample(Collection& c, unsigned short i, short j):
  Object(c, i, "HcalSample"),
  m_timeslice(j)
{}
