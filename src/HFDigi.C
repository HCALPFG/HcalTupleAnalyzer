#include "HFDigi.h"

HFDigi::HFDigi():
  HcalDigi(){}

HFDigi::HFDigi(Collection& c, unsigned short i, short j ):
  HcalDigi(c,i){}

float HFDigi::energy    () {return m_collection -> GetData() -> HFDigiRecEnergy  -> at(m_raw_index);}
float HFDigi::recHitTime() {return m_collection -> GetData() -> HFDigiRecTime    -> at(m_raw_index);}
int   HFDigi::ieta      () {return m_collection -> GetData() -> HFDigiIEta       -> at(m_raw_index);}
int   HFDigi::iphi      () {return m_collection -> GetData() -> HFDigiIPhi       -> at(m_raw_index);}
int   HFDigi::depth     () {return m_collection -> GetData() -> HFDigiDepth      -> at(m_raw_index);}
int   HFDigi::size      () {return m_collection -> GetData() -> HFDigiSize       -> at(m_raw_index);}
int   HFDigi::presamples() {return m_collection -> GetData() -> HFDigiPresamples -> at(m_raw_index);}
float HFDigi::fc   (int i) {return m_collection -> GetData() -> HFDigiFC         -> at(m_raw_index)[i];}
int   HFDigi::adc  (int i) {return m_collection -> GetData() -> HFDigiADC        -> at(m_raw_index)[i];}
