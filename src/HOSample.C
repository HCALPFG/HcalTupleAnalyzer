#include "HOSample.h"

HOSample::HOSample():
  HcalSample()
{}

HOSample::HOSample(Collection& c, unsigned short i, short j):
  HcalSample(c, i, j)
{}

float HOSample::allFC()     {return m_collection -> GetData() -> HODigiAllFC     -> at(m_raw_index)[m_timeslice];}
float HOSample::energy()    {return m_collection -> GetData() -> HODigiEnergy    -> at(m_raw_index)[m_timeslice];}
float HOSample::gain()      {return m_collection -> GetData() -> HODigiGain      -> at(m_raw_index)[m_timeslice];}
float HOSample::fc()        {return m_collection -> GetData() -> HODigiFC        -> at(m_raw_index)[m_timeslice];}
float HOSample::nomFC()     {return m_collection -> GetData() -> HODigiNomFC     -> at(m_raw_index)[m_timeslice];}
float HOSample::pedFC()     {return m_collection -> GetData() -> HODigiPedFC     -> at(m_raw_index)[m_timeslice];}
float HOSample::rcGain()    {return m_collection -> GetData() -> HODigiRCGain    -> at(m_raw_index)[m_timeslice];}

int   HOSample::adc()       {return m_collection -> GetData() -> HODigiADC       -> at(m_raw_index)[m_timeslice];}
int   HOSample::capid()     {return m_collection -> GetData() -> HODigiCapID     -> at(m_raw_index)[m_timeslice];}
int   HOSample::dv()        {return m_collection -> GetData() -> HODigiDV        -> at(m_raw_index)[m_timeslice];}
int   HOSample::er()        {return m_collection -> GetData() -> HODigiER        -> at(m_raw_index)[m_timeslice];}
int   HOSample::fiber()     {return m_collection -> GetData() -> HODigiFiber     -> at(m_raw_index)[m_timeslice];}
int   HOSample::fiberChan() {return m_collection -> GetData() -> HODigiFiberChan -> at(m_raw_index)[m_timeslice];}
int   HOSample::raw()       {return m_collection -> GetData() -> HODigiRaw       -> at(m_raw_index)[m_timeslice];}
