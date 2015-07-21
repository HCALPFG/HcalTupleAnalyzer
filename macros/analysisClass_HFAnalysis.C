#include "analysisClass.h"
#include "HcalTupleTree.h"
#include "HFDigi.h"

void analysisClass::loop(){
  
  //--------------------------------------------------------------------------------
  // Declare HCAL tree(s)
  //--------------------------------------------------------------------------------

  HcalTupleTree * tuple_tree = getTree<HcalTupleTree>("tuple_tree");
  int n_events = tuple_tree -> fChain -> GetEntries();
  std::cout << "n events = " << n_events << std::endl;
  
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
  tuple_tree -> fChain -> SetBranchStatus("HFDigiRecEnergy" , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiRecTime"   , kTRUE);

  
  //--------------------------------------------------------------------------------
  // Loop
  //--------------------------------------------------------------------------------
  int nHFDigis;

  float pedestalThreshold = 20;

  TH2F * badChannel_depth1 = makeTH2F("shift_depth1", 85, -42.5, 42.5, 72, 0.5, 72.5 );
  TH2F * badChannel_depth2 = makeTH2F("shift_depth2", 85, -42.5, 42.5, 72, 0.5, 72.5 );
  TH2F * averageTiming =  makeTH2F("averageTiming", 85, -42.5, 42.5, 72, 0.5, 72.5 );
  TH2F * count =  makeTH2F("count", 85, -42.5, 42.5, 72, 0.5, 72.5 );

  for (int i = 0; i < n_events; ++i){
    
    tuple_tree -> GetEntry(i);
    if ( (i + 1) % 1000 == 0 ) std::cout << "Processing event " << i + 1 << "/" << n_events << std::endl;

    CollectionPtr hfDigis (new Collection(*tuple_tree, tuple_tree -> HFDigiIEta -> size()));
    
    nHFDigis = hfDigis -> GetSize();

    for (int iHFDigi = 0; iHFDigi < nHFDigis; ++iHFDigi){
      HFDigi hfDigi = hfDigis -> GetConstituent<HFDigi>(iHFDigi);

      // averageTiming -> Fill(hfDigi.ieta(),hfDigi.iphi(),hfDigi.recHitTime());
      count -> Fill(hfDigi.ieta(),hfDigi.iphi());

      if ( (hfDigi.fc(0) > pedestalThreshold) or (hfDigi.fc(3) > pedestalThreshold ) ){
        if (hfDigi.depth() == 1){
          badChannel_depth1 -> Fill(hfDigi.ieta(),hfDigi.iphi());
        };
        if (hfDigi.depth() == 2){
          badChannel_depth2 -> Fill(hfDigi.ieta(),hfDigi.iphi());
        };
	


      };
      
      
    }
  }
  
  averageTiming -> Divide(count);

}
