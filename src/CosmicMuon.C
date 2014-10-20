#include "CosmicMuon.h"

CosmicMuon::CosmicMuon ():
  Object()
{}

CosmicMuon::CosmicMuon (Collection& c, unsigned short i, short j):
  Object (c,i, "CosmicMuon")
{}

double & CosmicMuon::Pt () { return m_collection -> GetData() -> CosmicMuonPt  -> at (m_raw_index); }
double & CosmicMuon::Eta() { return m_collection -> GetData() -> CosmicMuonEta -> at (m_raw_index); }
double & CosmicMuon::Phi() { return m_collection -> GetData() -> CosmicMuonPhi -> at (m_raw_index); }

std::ostream& operator<<(std::ostream& stream, CosmicMuon& object) {
  stream << object.Name() << " " << ": "
	 << "Pt = "  << object.Pt ()       << ", "
	 << "Eta = " << object.Eta()       << ", "
	 << "Phi = " << object.Phi();
  return stream;
}
