#include "analysisClass.h"
#include "HcalTupleTree.h"
#include "HcalTP.h"

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
  tuple_tree -> fChain -> SetBranchStatus("run", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("event", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("ls", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HcalTriggerPrimitiveCompressedEtSOI", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HcalTriggerPrimitiveIEta", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HcalTriggerPrimitiveIPhi", kTRUE);

  //--------------------------------------------------------------------------------
  // Make histograms
  //--------------------------------------------------------------------------------
  TH1F * h_et = makeTH1F("SumEt",100,0.,50.);
  TH1F * h_ieta = makeTH1F("ieta",59, -29.5, 29.5);
  TH1F * h_iphi = makeTH1F("iphi",72, 0.5, 72.5 );

  TH2F * h_ieta_vs_iphi_zeroEt = makeTH2F("h_ieta_vs_iphi_zeroEt",59, -29.5, 29.5, 72, 0.5, 72.5); 

  //--------------------------------------------------------------------------------
  // Loop
  //--------------------------------------------------------------------------------
  
  for (int i = 0; i < n_events; ++i){
    
    tuple_tree -> GetEntry(i);
    if ( (i + 1) % 1000 == 0 ) std::cout << "Processing event " << i + 1 << "/" << n_events << std::endl;
    
    //-----------------------------------------------------------------
    // Collections of Hcal Trigger Primitive 
    //-----------------------------------------------------------------
    CollectionPtr hcalTPs (new Collection(*tuple_tree, tuple_tree -> HcalTriggerPrimitiveIEta -> size()));
    
    int nHcalTPs = hcalTPs -> GetSize();
    // std::cout << "Number of HcalTP in this dataset:" <<  nHcalTPs << std::endl;
    for (int iHcalTP = 0; iHcalTP < nHcalTPs; ++iHcalTP){
      HcalTP hcalTP = hcalTPs -> GetConstituent<HcalTP>(iHcalTP);
      
      h_et -> Fill ( hcalTP.Et() );
      h_ieta -> Fill ( hcalTP.ieta() );
      h_iphi -> Fill ( hcalTP.iphi() );

      //-----------------------------------------------------------------
      // Validation Plot
      //-----------------------------------------------------------------
      if (hcalTP.Et() < 1.){
        h_ieta_vs_iphi_zeroEt -> Fill ( hcalTP.ieta() , hcalTP.iphi() );
      }; 

    };
  };
  
};
