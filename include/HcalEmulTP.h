#ifndef HcalEmulTP_H
#define HcalEmulTP_H

#include "Object.h"
#include "Collection.h"
// #include "HBHEDigi.h"
// #include "HFDigi.h"

class HcalEmulTP : public Object {

public:
  HcalEmulTP();
  HcalEmulTP(Collection& c, unsigned short i, short j = 0);

  float Et();
  int ieta();
  int iphi();
  int fineGrain();
  int presamples();
  // std::vector< int > HBHEIndices();
  
  double & Pt() { return m_null_value; } // Code will crash!
  double & Eta(){ return m_null_value; } // Code will crash!
  double & Phi(){ return m_null_value; } // Code will crash!

  bool PassUserID (ID id, bool verbose = false) {return false; }

  // HBHEDigi operator[] (int i){
  //   return HBHEDigi(*m_collection, m_raw_index, i );
 //  }
  


protected:
  double m_null_value;

};

#endif 
