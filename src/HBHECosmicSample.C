#include "HBHECosmicSample.h"

HBHECosmicSample::HBHECosmicSample():
  HcalSample()
{}

HBHECosmicSample::HBHECosmicSample(Collection& c, unsigned short i, short j):
  HcalSample(c, i, j)
{}

float HBHECosmicSample::allFC()     {return m_collection -> GetData() -> HBHECosmicDigiAllFC     -> at(m_raw_index)[m_timeslice];}
float HBHECosmicSample::energy()    {return m_collection -> GetData() -> HBHECosmicDigiEnergy    -> at(m_raw_index)[m_timeslice];}
float HBHECosmicSample::gain()      {return m_collection -> GetData() -> HBHECosmicDigiGain      -> at(m_raw_index)[m_timeslice];}
float HBHECosmicSample::fc()        {return m_collection -> GetData() -> HBHECosmicDigiFC        -> at(m_raw_index)[m_timeslice];}
float HBHECosmicSample::nomFC()     {return m_collection -> GetData() -> HBHECosmicDigiNomFC     -> at(m_raw_index)[m_timeslice];}
float HBHECosmicSample::pedFC()     {return m_collection -> GetData() -> HBHECosmicDigiPedFC     -> at(m_raw_index)[m_timeslice];}
float HBHECosmicSample::rcGain()    {return m_collection -> GetData() -> HBHECosmicDigiRCGain    -> at(m_raw_index)[m_timeslice];}

int   HBHECosmicSample::adc()       {return m_collection -> GetData() -> HBHECosmicDigiADC       -> at(m_raw_index)[m_timeslice];}
int   HBHECosmicSample::capid()     {return m_collection -> GetData() -> HBHECosmicDigiCapID     -> at(m_raw_index)[m_timeslice];}
int   HBHECosmicSample::dv()        {return m_collection -> GetData() -> HBHECosmicDigiDV        -> at(m_raw_index)[m_timeslice];}
int   HBHECosmicSample::er()        {return m_collection -> GetData() -> HBHECosmicDigiER        -> at(m_raw_index)[m_timeslice];}
int   HBHECosmicSample::fiber()     {return m_collection -> GetData() -> HBHECosmicDigiFiber     -> at(m_raw_index)[m_timeslice];}
int   HBHECosmicSample::fiberChan() {return m_collection -> GetData() -> HBHECosmicDigiFiberChan -> at(m_raw_index)[m_timeslice];}
int   HBHECosmicSample::raw()       {return m_collection -> GetData() -> HBHECosmicDigiRaw       -> at(m_raw_index)[m_timeslice];}
