#include "HBHECosmicDigi.h"

HBHECosmicDigi::HBHECosmicDigi():
  HcalDigi(){}

HBHECosmicDigi::HBHECosmicDigi(Collection& c, unsigned short i, short j ):
  HcalDigi(c,i){}

float HBHECosmicDigi::energy    () {return m_collection -> GetData() -> HBHECosmicDigiRecEnergy  -> at(m_raw_index);}
float HBHECosmicDigi::recHitTime() {return m_collection -> GetData() -> HBHECosmicDigiRecTime    -> at(m_raw_index);}
float HBHECosmicDigi::phi 		() {return m_collection -> GetData() -> HBHECosmicDigiPhi 		 -> at(m_raw_index);}
int   HBHECosmicDigi::ieta      () {return m_collection -> GetData() -> HBHECosmicDigiIEta       -> at(m_raw_index);}
int   HBHECosmicDigi::iphi      () {return m_collection -> GetData() -> HBHECosmicDigiIPhi       -> at(m_raw_index);}
int   HBHECosmicDigi::depth     () {return m_collection -> GetData() -> HBHECosmicDigiDepth      -> at(m_raw_index);}
int   HBHECosmicDigi::size      () {return m_collection -> GetData() -> HBHECosmicDigiSize       -> at(m_raw_index);}
int   HBHECosmicDigi::presamples() {return m_collection -> GetData() -> HBHECosmicDigiPresamples -> at(m_raw_index);}
float HBHECosmicDigi::fc   (int i) {return m_collection -> GetData() -> HBHECosmicDigiFC         -> at(m_raw_index)[i];}
int   HBHECosmicDigi::adc  (int i) {return m_collection -> GetData() -> HBHECosmicDigiADC        -> at(m_raw_index)[i];}
