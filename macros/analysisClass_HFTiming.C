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

  // TH2F * TS12Ratio_depth1 = makeTH2F("TS12Ratio_depth1", 85, -42.5, 42.5, 72, 0.5, 72.5 );
  TH1F * Q2_Q12_Ratio = makeTH1F("Q2_Q12_Ratio",100,0.,1.);
  TH1F * recHitTiming = makeTH1F("RecTiming",100,0,200.);

  for (int i = 0; i < n_events; ++i){
    
    tuple_tree -> GetEntry(i);
    if ( (i + 1) % 1000 == 0 ) std::cout << "Processing event " << i + 1 << "/" << n_events << std::endl;

    CollectionPtr hfDigis (new Collection(*tuple_tree, tuple_tree -> HFDigiIEta -> size()));
    
    nHFDigis = hfDigis -> GetSize();

    for (int iHFDigi = 0; iHFDigi < nHFDigis; ++iHFDigi){
      HFDigi hfDigi = hfDigis -> GetConstituent<HFDigi>(iHFDigi);

      float sum12 = hfDigi.fc(1)+hfDigi.fc(2);
      if (hfDigi.energy()) continue;
      // if (sum12 < 20.)  continue; 
      recHitTiming -> Fill(hfDigi.recHitTime());
      Q2_Q12_Ratio -> Fill( hfDigi.fc(2)/sum12 );

    }; 
  };
}
