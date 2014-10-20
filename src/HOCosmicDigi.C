#include "HOCosmicDigi.h"

HOCosmicDigi::HOCosmicDigi():
  HcalDigi(){}

HOCosmicDigi::HOCosmicDigi(Collection& c, unsigned short i, short j ):
  HcalDigi(c,i){}

float HOCosmicDigi::energy    () {return m_collection -> GetData() -> HOCosmicDigiRecEnergy  -> at(m_raw_index);}
float HOCosmicDigi::recHitTime() {return m_collection -> GetData() -> HOCosmicDigiRecTime    -> at(m_raw_index);}
int   HOCosmicDigi::ieta      () {return m_collection -> GetData() -> HOCosmicDigiIEta       -> at(m_raw_index);}
int   HOCosmicDigi::iphi      () {return m_collection -> GetData() -> HOCosmicDigiIPhi       -> at(m_raw_index);}
int   HOCosmicDigi::depth     () {return m_collection -> GetData() -> HOCosmicDigiDepth      -> at(m_raw_index);}
int   HOCosmicDigi::size      () {return m_collection -> GetData() -> HOCosmicDigiSize       -> at(m_raw_index);}
int   HOCosmicDigi::presamples() {return m_collection -> GetData() -> HOCosmicDigiPresamples -> at(m_raw_index);}
float HOCosmicDigi::fc   (int i) {return m_collection -> GetData() -> HOCosmicDigiFC         -> at(m_raw_index)[i];}
int   HOCosmicDigi::adc  (int i) {return m_collection -> GetData() -> HOCosmicDigiADC        -> at(m_raw_index)[i];}
