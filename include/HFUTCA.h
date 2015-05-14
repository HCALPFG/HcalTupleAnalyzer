#ifndef HF_UTCA_H
#define HF_UTCA_H

#include "HcalDigi.h"
#include "HFUTCASample.h"

class HFUTCA : public HcalDigi {

 public:
  HFUTCA();
  HFUTCA(Collection& c, unsigned short i, short j = 0);
  
  float energy() ;
  float recHitTime  () ;
  int   ieta  () ;
  int   iphi  () ;
  int   depth () ;
  int   size  () ;
  int   presamples() ;
  int   rawId        () ;
  int   electronicsId() ;
  float fc (int i);
  int adc(int i);
  int dv (int i);
  int er (int i);
  int capid (int i);
  
  int getRawIndex () { return m_raw_index; }

  HFUTCASample operator[] ( int i ){
    return HFUTCASample( *m_collection, m_raw_index, i );
  }
  
};

#endif 
