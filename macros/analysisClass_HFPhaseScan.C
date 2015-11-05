#include "analysisClass.h"
#include "HcalTupleTree.h"
#include "HFDigi.h"
#include <map>

int getHash ( const int & ieta, 
	      const int & iphi, 
	      const int & depth ){
  int ietaIndex = ieta + 41;
  int iphiIndex = iphi;
  int depthIndex = depth;
  
  int hash = 0;
  hash += (ietaIndex * 1);
  hash += (iphiIndex * 100);
  hash += (depthIndex * 10000);
  return hash;
}

void reverseHash ( const int & hash,
		   int & ieta,
		   int & iphi,
		   int & depth ){
  int tmp_hash = hash;
  ieta = (hash % 100) - 41;
  iphi = (hash / 100) % 100;
  depth = (hash / 10000);
}
	      

void analysisClass::loop(){
  
  //--------------------------------------------------------------------------------
  // Declare HCAL tree(s)
  //--------------------------------------------------------------------------------

  HcalTupleTree * tuple_tree = getTree<HcalTupleTree>("tuple_tree");
  int n_events = tuple_tree -> fChain -> GetEntries();
  std::cout << "n events = " << n_events << std::endl;
  
  double min_charge12 = 50.;
  
  //--------------------------------------------------------------------------------
  // Turn on/off branches
  //--------------------------------------------------------------------------------
  
  tuple_tree -> fChain -> SetBranchStatus("*"               , kFALSE);
  tuple_tree -> fChain -> SetBranchStatus("run"             , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("event"           , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("ls"              , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiFC"        , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiDepth"     , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiIEta"      , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiIPhi"      , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiSize"      , kTRUE);
  
  //--------------------------------------------------------------------------------
  // Loop
  //--------------------------------------------------------------------------------
  
  int hash; 
  int nHFDigis;
  double timing12 = 0.;
  double charge12 = 0.;
  char hist_name[200];
  
  std::map<int, TH1F*> map_hash_timing12;
  std::map<int, TH1F*>::iterator map_it;

  for (int i = 0; i < n_events; ++i){
    
    tuple_tree -> GetEntry(i);
    if ( (i + 1) % 1000 == 0 ) std::cout << "Processing event " << i + 1 << "/" << n_events << std::endl;

    CollectionPtr hfDigis (new Collection(*tuple_tree, tuple_tree -> HFDigiIEta -> size()));
    
    nHFDigis = hfDigis -> GetSize();

    for (int iHFDigi = 0; iHFDigi < nHFDigis; ++iHFDigi){
      HFDigi hfDigi = hfDigis -> GetConstituent<HFDigi>(iHFDigi);
      
      hash = getHash ( hfDigi.ieta(), hfDigi.iphi(), hfDigi.depth());
      charge12 = hfDigi.charge12();
      timing12 = hfDigi.time12();
      map_it = map_hash_timing12.find (hash);
      
      if ( map_hash_timing12.find (hash) == map_hash_timing12.end() ){
	sprintf(hist_name, "HF_%d_%d_%d", hfDigi.ieta(), hfDigi.iphi(), hfDigi.depth());
	map_hash_timing12.insert(std::pair<int, TH1F*>(hash, makeTH1F(hist_name, 200, 0.0, 5.0)));
      }
      
      if ( charge12 > min_charge12 ) map_hash_timing12[hash] -> Fill ( timing12 );
      
    }
  }
}
