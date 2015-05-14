#include "HFUTCA.h"

HFUTCA::HFUTCA():
  HcalDigi(){}

HFUTCA::HFUTCA(Collection& c, unsigned short i, short j ):
  HcalDigi(c,i){}

float HFUTCA::energy       () {return m_collection -> GetData() -> HFUTCARecEnergy     -> at(m_raw_index);}
float HFUTCA::recHitTime   () {return m_collection -> GetData() -> HFUTCARecTime       -> at(m_raw_index);}
int   HFUTCA::ieta         () {return m_collection -> GetData() -> HFUTCAIEta          -> at(m_raw_index);}
int   HFUTCA::iphi         () {return m_collection -> GetData() -> HFUTCAIPhi          -> at(m_raw_index);}
int   HFUTCA::depth        () {return m_collection -> GetData() -> HFUTCADepth         -> at(m_raw_index);}
int   HFUTCA::size         () {return m_collection -> GetData() -> HFUTCASize          -> at(m_raw_index);}
int   HFUTCA::presamples   () {return m_collection -> GetData() -> HFUTCAPresamples    -> at(m_raw_index);}
int   HFUTCA::rawId        () {return m_collection -> GetData() -> HFUTCARawID         -> at(m_raw_index);}
int   HFUTCA::electronicsId() {return m_collection -> GetData() -> HFUTCAElectronicsID -> at(m_raw_index);}
float HFUTCA::fc      (int i) {return m_collection -> GetData() -> HFUTCAFC            -> at(m_raw_index)[i];}
int   HFUTCA::adc     (int i) {return m_collection -> GetData() -> HFUTCAADC           -> at(m_raw_index)[i];}
int   HFUTCA::dv      (int i) {return m_collection -> GetData() -> HFUTCADV            -> at(m_raw_index)[i];}
int   HFUTCA::er      (int i) {return m_collection -> GetData() -> HFUTCAER            -> at(m_raw_index)[i];}
int   HFUTCA::capid   (int i) {return m_collection -> GetData() -> HFUTCACapID         -> at(m_raw_index)[i];}
