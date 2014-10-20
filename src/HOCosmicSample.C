#include "HOCosmicSample.h"

HOCosmicSample::HOCosmicSample():
  HcalSample()
{}

HOCosmicSample::HOCosmicSample(Collection& c, unsigned short i, short j):
  HcalSample(c, i, j)
{}

float HOCosmicSample::allFC()     {return m_collection -> GetData() -> HOCosmicDigiAllFC     -> at(m_raw_index)[m_timeslice];}
float HOCosmicSample::energy()    {return m_collection -> GetData() -> HOCosmicDigiEnergy    -> at(m_raw_index)[m_timeslice];}
float HOCosmicSample::gain()      {return m_collection -> GetData() -> HOCosmicDigiGain      -> at(m_raw_index)[m_timeslice];}
float HOCosmicSample::fc()        {return m_collection -> GetData() -> HOCosmicDigiFC        -> at(m_raw_index)[m_timeslice];}
float HOCosmicSample::nomFC()     {return m_collection -> GetData() -> HOCosmicDigiNomFC     -> at(m_raw_index)[m_timeslice];}
float HOCosmicSample::pedFC()     {return m_collection -> GetData() -> HOCosmicDigiPedFC     -> at(m_raw_index)[m_timeslice];}
float HOCosmicSample::rcGain()    {return m_collection -> GetData() -> HOCosmicDigiRCGain    -> at(m_raw_index)[m_timeslice];}

int   HOCosmicSample::adc()       {return m_collection -> GetData() -> HOCosmicDigiADC       -> at(m_raw_index)[m_timeslice];}
int   HOCosmicSample::capid()     {return m_collection -> GetData() -> HOCosmicDigiCapID     -> at(m_raw_index)[m_timeslice];}
int   HOCosmicSample::dv()        {return m_collection -> GetData() -> HOCosmicDigiDV        -> at(m_raw_index)[m_timeslice];}
int   HOCosmicSample::er()        {return m_collection -> GetData() -> HOCosmicDigiER        -> at(m_raw_index)[m_timeslice];}
int   HOCosmicSample::fiber()     {return m_collection -> GetData() -> HOCosmicDigiFiber     -> at(m_raw_index)[m_timeslice];}
int   HOCosmicSample::fiberChan() {return m_collection -> GetData() -> HOCosmicDigiFiberChan -> at(m_raw_index)[m_timeslice];}
int   HOCosmicSample::raw()       {return m_collection -> GetData() -> HOCosmicDigiRaw       -> at(m_raw_index)[m_timeslice];}
