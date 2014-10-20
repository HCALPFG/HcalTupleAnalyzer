#include "HFSample.h"

HFSample::HFSample():
  HcalSample()
{}

HFSample::HFSample(Collection& c, unsigned short i, short j):
  HcalSample(c, i, j)
{}

float HFSample::allFC()     {return m_collection -> GetData() -> HFDigiAllFC     -> at(m_raw_index)[m_timeslice];}
float HFSample::energy()    {return m_collection -> GetData() -> HFDigiEnergy    -> at(m_raw_index)[m_timeslice];}
float HFSample::gain()      {return m_collection -> GetData() -> HFDigiGain      -> at(m_raw_index)[m_timeslice];}
float HFSample::fc()        {return m_collection -> GetData() -> HFDigiFC        -> at(m_raw_index)[m_timeslice];}
float HFSample::nomFC()     {return m_collection -> GetData() -> HFDigiNomFC     -> at(m_raw_index)[m_timeslice];}
float HFSample::pedFC()     {return m_collection -> GetData() -> HFDigiPedFC     -> at(m_raw_index)[m_timeslice];}
float HFSample::rcGain()    {return m_collection -> GetData() -> HFDigiRCGain    -> at(m_raw_index)[m_timeslice];}

int   HFSample::adc()       {return m_collection -> GetData() -> HFDigiADC       -> at(m_raw_index)[m_timeslice];}
int   HFSample::capid()     {return m_collection -> GetData() -> HFDigiCapID     -> at(m_raw_index)[m_timeslice];}
int   HFSample::dv()        {return m_collection -> GetData() -> HFDigiDV        -> at(m_raw_index)[m_timeslice];}
int   HFSample::er()        {return m_collection -> GetData() -> HFDigiER        -> at(m_raw_index)[m_timeslice];}
int   HFSample::fiber()     {return m_collection -> GetData() -> HFDigiFiber     -> at(m_raw_index)[m_timeslice];}
int   HFSample::fiberChan() {return m_collection -> GetData() -> HFDigiFiberChan -> at(m_raw_index)[m_timeslice];}
int   HFSample::raw()       {return m_collection -> GetData() -> HFDigiRaw       -> at(m_raw_index)[m_timeslice];}
