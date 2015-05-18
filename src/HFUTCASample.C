#include "HFUTCASample.h"

HFUTCASample::HFUTCASample():
  HcalSample()
{}

HFUTCASample::HFUTCASample(Collection& c, unsigned short i, short j):
  HcalSample(c, i, j)
{}

float HFUTCASample::allFC()     {return m_collection -> GetData() -> HFUTCAAllFC     -> at(m_raw_index)[m_timeslice];}
float HFUTCASample::energy()    {return m_collection -> GetData() -> HFUTCAEnergy    -> at(m_raw_index)[m_timeslice];}
float HFUTCASample::gain()      {return m_collection -> GetData() -> HFUTCAGain      -> at(m_raw_index)[m_timeslice];}
float HFUTCASample::fc()        {return m_collection -> GetData() -> HFUTCAFC        -> at(m_raw_index)[m_timeslice];}
float HFUTCASample::nomFC()     {return m_collection -> GetData() -> HFUTCANomFC     -> at(m_raw_index)[m_timeslice];}
float HFUTCASample::pedFC()     {return m_collection -> GetData() -> HFUTCAPedFC     -> at(m_raw_index)[m_timeslice];}
float HFUTCASample::rcGain()    {return m_collection -> GetData() -> HFUTCARCGain    -> at(m_raw_index)[m_timeslice];}

int   HFUTCASample::adc()       {return m_collection -> GetData() -> HFUTCAADC       -> at(m_raw_index)[m_timeslice];}
int   HFUTCASample::capid()     {return m_collection -> GetData() -> HFUTCACapID     -> at(m_raw_index)[m_timeslice];}
int   HFUTCASample::dv()        {return m_collection -> GetData() -> HFUTCADV        -> at(m_raw_index)[m_timeslice];}
int   HFUTCASample::er()        {return m_collection -> GetData() -> HFUTCAER        -> at(m_raw_index)[m_timeslice];}
int   HFUTCASample::fiber()     {return m_collection -> GetData() -> HFUTCAFiber     -> at(m_raw_index)[m_timeslice];}
int   HFUTCASample::fiberChan() {return m_collection -> GetData() -> HFUTCAFiberChan -> at(m_raw_index)[m_timeslice];}
int   HFUTCASample::raw()       {return m_collection -> GetData() -> HFUTCARaw       -> at(m_raw_index)[m_timeslice];}
