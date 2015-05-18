#ifndef HO_DIGI_H
#define HO_DIGI_H

#include "HcalDigi.h"
#include "HOSample.h"

class HODigi : public HcalDigi {

 public:
  HODigi();
  HODigi(Collection& c, unsigned short i, short j = 0);
  
  float energy() ;
  float recHitTime  () ;
  int   ieta  () ;
  int   iphi  () ;
  int   depth () ;
  int   size  () ;
  int   presamples() ;
  int   electronicsId();
  int   rawId();
  float fc (int i);
  int adc(int i);
  int dv (int i);
  int er (int i);
  int capid (int i);
  
  int getRawIndex () { return m_raw_index; }

  HOSample operator[] ( int i ){
    return HOSample( *m_collection, m_raw_index, i );
  }
  
};

#endif 
