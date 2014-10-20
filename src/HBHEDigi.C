#include "HBHEDigi.h"

HBHEDigi::HBHEDigi():
  HcalDigi(){}

HBHEDigi::HBHEDigi(Collection& c, unsigned short i, short j ):
  HcalDigi(c,i){}

float HBHEDigi::energy    () {return m_collection -> GetData() -> HBHEDigiRecEnergy  -> at(m_raw_index);}
float HBHEDigi::recHitTime() {return m_collection -> GetData() -> HBHEDigiRecTime    -> at(m_raw_index);}
int   HBHEDigi::ieta      () {return m_collection -> GetData() -> HBHEDigiIEta       -> at(m_raw_index);}
int   HBHEDigi::iphi      () {return m_collection -> GetData() -> HBHEDigiIPhi       -> at(m_raw_index);}
int   HBHEDigi::depth     () {return m_collection -> GetData() -> HBHEDigiDepth      -> at(m_raw_index);}
int   HBHEDigi::size      () {return m_collection -> GetData() -> HBHEDigiSize       -> at(m_raw_index);}
int   HBHEDigi::presamples() {return m_collection -> GetData() -> HBHEDigiPresamples -> at(m_raw_index);}
float HBHEDigi::fc   (int i) {return m_collection -> GetData() -> HBHEDigiFC         -> at(m_raw_index)[i];}
int   HBHEDigi::adc  (int i) {return m_collection -> GetData() -> HBHEDigiADC        -> at(m_raw_index)[i];}
