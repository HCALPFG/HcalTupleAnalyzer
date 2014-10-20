#ifndef HF_DIGI_H
#define HF_DIGI_H

#include "HcalDigi.h"
#include "HFSample.h"

class HFDigi : public HcalDigi {

 public:
  HFDigi();
  HFDigi(Collection& c, unsigned short i, short j = 0);
  
  float energy() ;
  float recHitTime  () ;
  int   ieta  () ;
  int   iphi  () ;
  int   depth () ;
  int   size  () ;
  int   presamples() ;
  float fc (int i);
  int adc(int i);
  
  int getRawIndex () { return m_raw_index; }

  HFSample operator[] ( int i ){
    return HFSample( *m_collection, m_raw_index, i );
  }
  
};

#endif 
