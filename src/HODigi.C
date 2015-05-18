#include "HODigi.h"

HODigi::HODigi():
  HcalDigi(){}

HODigi::HODigi(Collection& c, unsigned short i, short j ):
  HcalDigi(c,i){}

float HODigi::energy       () {return m_collection -> GetData() -> HODigiRecEnergy     -> at(m_raw_index);}
float HODigi::recHitTime   () {return m_collection -> GetData() -> HODigiRecTime       -> at(m_raw_index);}
int   HODigi::ieta         () {return m_collection -> GetData() -> HODigiIEta          -> at(m_raw_index);}
int   HODigi::iphi         () {return m_collection -> GetData() -> HODigiIPhi          -> at(m_raw_index);}
int   HODigi::depth        () {return m_collection -> GetData() -> HODigiDepth         -> at(m_raw_index);}
int   HODigi::size         () {return m_collection -> GetData() -> HODigiSize          -> at(m_raw_index);}
int   HODigi::presamples   () {return m_collection -> GetData() -> HODigiPresamples    -> at(m_raw_index);}
int   HODigi::rawId        () {return -1; }
int   HODigi::electronicsId() {return -1; }
float HODigi::fc      (int i) {return m_collection -> GetData() -> HODigiFC            -> at(m_raw_index)[i];}
int   HODigi::adc     (int i) {return m_collection -> GetData() -> HODigiADC           -> at(m_raw_index)[i];}
int   HODigi::dv      (int i) {return m_collection -> GetData() -> HODigiDV            -> at(m_raw_index)[i];}
int   HODigi::er      (int i) {return m_collection -> GetData() -> HODigiER            -> at(m_raw_index)[i];}
int   HODigi::capid   (int i) {return m_collection -> GetData() -> HODigiCapID         -> at(m_raw_index)[i];}
