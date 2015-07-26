#include "analysisClass.h"
#include "HcalTupleTree.h"
#include "HcalTP.h"
#include "HBHEDigi.h"


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
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiIEta"      , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiIPhi"      , kTRUE); 
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiRecEnergy"      , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiADC"      , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HcalTriggerPrimitiveHBHEDigiIndex" , kTRUE);

  //--------------------------------------------------------------------------------
  // Make histograms
  //--------------------------------------------------------------------------------
  TH1F * h_et = makeTH1F("SumEt",100,0.,50.);
  TH1F * h_ieta = makeTH1F("ieta",59, -29.5, 29.5);
  TH1F * h_iphi = makeTH1F("iphi",72, 0.5, 72.5 );
  TH2F * h_ieta_vs_iphi = makeTH2F("ieta_vs_iphi",59, -29.5, 29.5,72, 0.5, 72.5 );
  TH1F * h_adc = makeTH1F("adc",100,0.,10.);
  
  //-----------------------------------------------------------------
  // Validation Plot
  //-----------------------------------------------------------------
  // TH1F * h_linADC = makeTH1F("linADC_DigiFromZeroTP",100,0.,10.);
  // TH2F * h_ieta_vs_iphi_zeroEt = makeTH2F("h_ieta_vs_iphi_zeroEt",59, -29.5, 29.5, 72, 0.5, 72.5);
  // TH2F * h_ieta_vs_iphi = makeTH2F("ieta_vs_iphi_DigiFromZeroTP",59, -29.5, 29.5, 72, 0.5, 72.5);


  //--------------------------------------------------------------------------------
  // Loop
  //--------------------------------------------------------------------------------
  
  for (int i = 0; i < n_events; ++i){
    
    tuple_tree -> GetEntry(i);
    if ( (i + 1) % 1000 == 0 ) std::cout << "Processing event " << i + 1 << "/" << n_events << std::endl;
    
    int RunNumber = tuple_tree -> run ;
    int EventNumber = tuple_tree -> event ;
    int LumiSection = tuple_tree -> ls ;


    //-----------------------------------------------------------------
    // Collections of Hcal Trigger Primitive 
    //-----------------------------------------------------------------
    CollectionPtr hcalTPs (new Collection(*tuple_tree, tuple_tree -> HcalTriggerPrimitiveIEta -> size()));
    CollectionPtr hbheDigis (new Collection(*tuple_tree, tuple_tree -> HBHEDigiIEta -> size()));
    int nHBHEDigis = hbheDigis -> GetSize();
    // for (int iHBHEDigi = 0; iHBHEDigi < nHBHEDigis; ++iHBHEDigi){
    //  HBHEDigi hbheDigi = hbheDigis -> GetConstituent<HBHEDigi>(iHBHEDigi);

    //  h_adc -> Fill(hbheDigi.adc(4));

    // }; 

    int nHcalTPs = hcalTPs -> GetSize();
    // std::cout << "Number of HcalTP in this dataset:" <<  nHcalTPs << std::endl;
    for (int iHcalTP = 0; iHcalTP < nHcalTPs; ++iHcalTP){
      HcalTP hcalTP = hcalTPs -> GetConstituent<HcalTP>(iHcalTP);
      
      h_et -> Fill ( hcalTP.Et() );
      h_ieta -> Fill ( hcalTP.ieta() );
      h_iphi -> Fill ( hcalTP.iphi() );

      if (hcalTP.Et() == -1){
	h_ieta_vs_iphi -> Fill(hcalTP.ieta(),hcalTP.iphi());
        fprintf(f, "%i %i %i %i %i \n", RunNumber, LumiSection, EventNumber , hcalTP.ieta() , hcalTP.iphi() );
      };
      

      //-----------------------------------------------------------------
      // Validation Plot
      //-----------------------------------------------------------------
     //  bool zeroADC = false;
     //  if (hcalTP.Et() < 1.){
     //    h_ieta_vs_iphi_zeroEt -> Fill ( hcalTP.ieta() , hcalTP.iphi() );
     //    for (int iHBHE = 0; iHBHE != hcalTP.HBHEIndices().size() ; ++iHBHE){
     //      HBHEDigi hbheDigi = hbheDigis -> GetConstituent<HBHEDigi>(  hcalTP.HBHEIndices()[iHBHE] );
     //      h_linADC -> Fill(hbheDigi.adc(2));
     //      h_ieta_vs_iphi -> Fill(hbheDigi.ieta(),hbheDigi.iphi());
     //      if (hbheDigi.adc(4) > 7){
     //        zeroADC = true; 
     //      };
     //    };
     //  };

     // if (zeroADC){
     //   fprintf(f, "%i %i %i %i %i \n", RunNumber, LumiSection, EventNumber , hcalTP.ieta() , hcalTP.iphi() );
     //  };

    };
  };
  
};
