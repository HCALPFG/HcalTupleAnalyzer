#include "HcalTP.h"

HcalTP::HcalTP(){}


HcalTP::HcalTP(Collection& c, unsigned short i, short j ):
  Object(c,i){}


float HcalTP::Et() {return m_collection -> GetData() -> HcalTriggerPrimitiveCompressedEtSOI  -> at(m_raw_index);};
int HcalTP::ieta() {return m_collection -> GetData() -> HcalTriggerPrimitiveIEta     -> at(m_raw_index);};
int HcalTP::iphi() {return m_collection -> GetData() -> HcalTriggerPrimitiveIPhi             -> at(m_raw_index);};
int HcalTP::fineGrain() {return m_collection -> GetData() -> HcalTriggerPrimitiveFineGrainSOI             -> at(m_raw_index);};
int HcalTP::presamples() {return m_collection -> GetData() -> HcalTriggerPrimitivePresamples       -> at(m_raw_index);};
std::vector < int > HcalTP::HBHEIndices() {return m_collection -> GetData() -> HcalTriggerPrimitiveHBHEDigiIndex -> at(m_raw_index);};
