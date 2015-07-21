#ifndef HcalTP_H
#define HcalTP_H

#include "Object.h"
#include "Collection.h"

class HcalTP : public Object {

public:
  HcalTP();
  HcalTP(Collection& c, unsigned short i, short j = 0);

  float Et();
  int ieta();
  int iphi();
  int fineGrain();
  int presamples();
  
  double & Pt() { return m_null_value; } // Code will crash!
  double & Eta(){ return m_null_value; } // Code will crash!
  double & Phi(){ return m_null_value; } // Code will crash!

  bool PassUserID (ID id, bool verbose = false) {return false; }


  double m_null_value;

};

#endif 
