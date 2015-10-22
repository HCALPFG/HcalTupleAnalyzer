#include "HcalEmulTP.h"

HcalEmulTP::HcalEmulTP(){}


HcalEmulTP::HcalEmulTP(Collection& c, unsigned short i, short j ):
  Object(c,i){}


float HcalEmulTP::Et() {return m_collection -> GetData() -> HcalEmulTriggerPrimitiveCompressedEtSOI  -> at(m_raw_index);};
int HcalEmulTP::ieta() {return m_collection -> GetData() -> HcalEmulTriggerPrimitiveIEta     -> at(m_raw_index);};
int HcalEmulTP::iphi() {return m_collection -> GetData() -> HcalEmulTriggerPrimitiveIPhi             -> at(m_raw_index);};
int HcalEmulTP::fineGrain() {return m_collection -> GetData() -> HcalEmulTriggerPrimitiveFineGrainSOI             -> at(m_raw_index);};
int HcalEmulTP::presamples() {return m_collection -> GetData() -> HcalEmulTriggerPrimitivePresamples       -> at(m_raw_index);};
