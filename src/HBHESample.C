#include "HBHESample.h"

HBHESample::HBHESample():
  HcalSample()
{}

HBHESample::HBHESample(Collection& c, unsigned short i, short j):
  HcalSample(c, i, j)
{}

float HBHESample::allFC()     {return m_collection -> GetData() -> HBHEDigiAllFC     -> at(m_raw_index)[m_timeslice];}
float HBHESample::energy()    {return m_collection -> GetData() -> HBHEDigiEnergy    -> at(m_raw_index)[m_timeslice];}
float HBHESample::gain()      {return m_collection -> GetData() -> HBHEDigiGain      -> at(m_raw_index)[m_timeslice];}
float HBHESample::fc()        {return m_collection -> GetData() -> HBHEDigiFC        -> at(m_raw_index)[m_timeslice];}
float HBHESample::nomFC()     {return m_collection -> GetData() -> HBHEDigiNomFC     -> at(m_raw_index)[m_timeslice];}
float HBHESample::pedFC()     {return m_collection -> GetData() -> HBHEDigiPedFC     -> at(m_raw_index)[m_timeslice];}
float HBHESample::rcGain()    {return m_collection -> GetData() -> HBHEDigiRCGain    -> at(m_raw_index)[m_timeslice];}

int   HBHESample::adc()       {return m_collection -> GetData() -> HBHEDigiADC       -> at(m_raw_index)[m_timeslice];}
int   HBHESample::capid()     {return m_collection -> GetData() -> HBHEDigiCapID     -> at(m_raw_index)[m_timeslice];}
int   HBHESample::dv()        {return m_collection -> GetData() -> HBHEDigiDV        -> at(m_raw_index)[m_timeslice];}
int   HBHESample::er()        {return m_collection -> GetData() -> HBHEDigiER        -> at(m_raw_index)[m_timeslice];}
int   HBHESample::fiber()     {return m_collection -> GetData() -> HBHEDigiFiber     -> at(m_raw_index)[m_timeslice];}
int   HBHESample::fiberChan() {return m_collection -> GetData() -> HBHEDigiFiberChan -> at(m_raw_index)[m_timeslice];}
int   HBHESample::raw()       {return m_collection -> GetData() -> HBHEDigiRaw       -> at(m_raw_index)[m_timeslice];}
