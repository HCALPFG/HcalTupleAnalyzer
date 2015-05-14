#include "analysisClass.h"
#include "HcalTupleTree.h"
#include "HFDigi.h"
#include "HFUTCA.h"

int findIndex ( const int & id, const std::vector<int> * ids ){
  std::vector<int>::const_iterator lower_bound = ids -> begin();
  std::vector<int>::const_iterator upper_bound = ids -> end();
  std::vector<int>::const_iterator mid_point;

  int distance = std::distance(lower_bound, upper_bound);
  int half_distance, retval;

  while ( distance > 0 ) { 
    half_distance = distance / 2;
    mid_point = lower_bound;
    std::advance(mid_point, half_distance);
    if ( *mid_point < id ) {
      lower_bound = mid_point;
      ++lower_bound;
      distance = distance - half_distance - 1;
    }
    else { 
      distance = half_distance;
    }
  }

  retval = (*mid_point == id) ? std::distance ( ids -> begin(), lower_bound ) : -1;
  return retval;
}

void analysisClass::loop(){
  
  //--------------------------------------------------------------------------------
  // Declare HCAL tree(s)
  //--------------------------------------------------------------------------------

  HcalTupleTree * tuple_tree = getTree<HcalTupleTree>("tuple_tree");
  int n_events = tuple_tree -> fChain -> GetEntries();

  //--------------------------------------------------------------------------------
  // Turn on/off branches
  //--------------------------------------------------------------------------------
  
  tuple_tree -> fChain -> SetBranchStatus("*"               , kFALSE);
  tuple_tree -> fChain -> SetBranchStatus("run", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("event", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("ls", kTRUE);

  tuple_tree -> fChain -> SetBranchStatus("HFDigiEta", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiPhi", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiRecEnergy", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiRecTime", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiAllFC", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiEnergy", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiFC", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiGain", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiNomFC", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiPedFC", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiRCGain", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiDepth", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiFiberIdleOffset", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiIEta", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiIPhi", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiPresamples", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiSize", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiADC", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiCapID", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiDV", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiER", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiFiber", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiFiberChan", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiRaw", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiRawID", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiElectronicsID", kTRUE);

  tuple_tree -> fChain -> SetBranchStatus("HFUTCAEta", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFUTCAPhi", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFUTCARecEnergy", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFUTCARecTime", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFUTCAAllFC", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFUTCAEnergy", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFUTCAFC", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFUTCAGain", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFUTCANomFC", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFUTCAPedFC", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFUTCARCGain", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFUTCADepth", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFUTCAFiberIdleOffset", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFUTCAIEta", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFUTCAIPhi", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFUTCAPresamples", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFUTCASize", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFUTCAADC", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFUTCACapID", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFUTCADV", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFUTCAER", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFUTCAFiber", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFUTCAFiberChan", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFUTCARaw", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFUTCARawID", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFUTCAElectronicsID", kTRUE);
  
  //--------------------------------------------------------------------------------
  // Make histograms
  //--------------------------------------------------------------------------------

  TH1F * h_utca_size         = makeTH1F ("utca_size"        , 21, -0.5, 20.5 );
  TH2F * h_vme_vs_utca_adc   = makeTH2F ("vme_vs_utca_adc"  , 129,  -1.5, 127.5, 129, -1.5, 127.5 );
  TH2F * h_occ_utca_bad_size = makeTH2F ("occ_utca_bad_size", 85, -42.5, 42.5, 72,  0.5, 72.5 );
  TH2F * h_occ_utca_mismatch = makeTH2F ("occ_utca_mismatch", 85, -42.5, 42.5, 72,  0.5, 72.5 );
  
  //--------------------------------------------------------------------------------
  // Loop
  //--------------------------------------------------------------------------------
  
  for (int i = 0; i < n_events; ++i){
    
    tuple_tree -> GetEntry(i);
    if ( (i + 1) % 100 == 0 ) std::cout << "Processing event " << i + 1 << "/" << n_events << std::endl;

    CollectionPtr utcaDigis  (new Collection(*tuple_tree, tuple_tree -> HFUTCAIEta -> size()));
    CollectionPtr vmeDigis   (new Collection(*tuple_tree, tuple_tree -> HFDigiIEta -> size()));
    
    int nUTCADigis = utcaDigis -> GetSize();
    for (int iUTCADigi = 0; iUTCADigi < nUTCADigis; ++iUTCADigi ){

      HFUTCA utcaDigi = utcaDigis -> GetConstituent<HFUTCA>(iUTCADigi);
      int utca_size = utcaDigi.size();
      if ( utca_size != 10 ) h_occ_utca_bad_size -> Fill ( utcaDigi.ieta(), utcaDigi.iphi() );

      h_utca_size -> Fill(utcaDigi.size() );
      int vme_index = findIndex ( utcaDigi.rawId(), tuple_tree -> HFDigiRawID);
      bool found_digi (vme_index >= 0);
      if ( !found_digi ) continue;
      
      HFDigi vmeDigi ( *vmeDigis, vme_index );

      int vme_size = vmeDigi.size();
      
      if ( utca_size == 10 ) { 
	for (int vmeTS = 0; vmeTS < vme_size ; ++vmeTS){
	  int utcaTS = vmeTS + 2;
	  int vmeADC = vmeDigi.adc(vmeTS);
	  int utcaADC = ( utcaTS > utca_size ) ? -1 : utcaDigi.adc(utcaTS);
	  h_vme_vs_utca_adc -> Fill ( vmeADC, utcaADC ) ;
	  if ( vmeADC != utcaADC ) {
	    h_occ_utca_mismatch -> Fill ( utcaDigi.ieta(), utcaDigi.iphi() );
	  }
	}
      }
    }
  }
}
