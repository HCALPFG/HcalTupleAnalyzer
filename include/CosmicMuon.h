#ifndef COSMIC_MUON_H
#define COSMIC_MUON_H

#include "Object.h"
#include "Collection.h"

class CosmicMuon : public Object {
  
 public:

  CosmicMuon();
  CosmicMuon(Collection& c, unsigned short i, short j = 0);

  double & Pt();
  double & Eta();
  double & Phi();
  
  bool PassUserID (ID id, bool b = false) { return false; }

  
};

std::ostream& operator<< (std::ostream& stream, CosmicMuon& object);

#endif
