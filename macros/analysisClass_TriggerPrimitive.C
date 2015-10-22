#include "analysisClass.h"
#include "HcalTupleTree.h"
#include "HcalTP.h"
#include "HcalEmulTP.h"
#include <fstream>


void analysisClass::loop(){


  
  //--------------------------------------------------------------------------------
  // Configurables
  //--------------------------------------------------------------------------------
  std::vector<int> selectIPhis = {19,21,23,25};
 
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
  tuple_tree -> fChain -> SetBranchStatus("HcalTriggerPrimitiveCompressedEtSOI",kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HcalEmulTriggerPrimitiveCompressedEtSOI",kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HcalTriggerPrimitiveIEta",kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HcalEmulTriggerPrimitiveIEta",kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HcalTriggerPrimitiveIPhi",kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HcalEmulTriggerPrimitiveIPhi",kTRUE);

  //--------------------------------------------------------------------------------
  // Make histograms
  //--------------------------------------------------------------------------------
  char histName[100];
  std::map<int,std::map<int,TH2F*>> h_emulTPEt_vs_TPEt;
  h_emulTPEt_vs_TPEt[1] = std::map<int,TH2F*>();
  h_emulTPEt_vs_TPEt[2] = std::map<int,TH2F*>();
  
  for (int iIPhi = 0; iIPhi != selectIPhis.size(); ++iIPhi){
    sprintf(histName,"h_emulTPEt_vs_TPEt_1_%d",selectIPhis[iIPhi]);
    h_emulTPEt_vs_TPEt[1][selectIPhis[iIPhi]] = makeTH2F(histName,50,0.,100.,50,0.,100.);
    sprintf(histName,"h_emulTPEt_vs_TPEt_2_%d",selectIPhis[iIPhi]);
    h_emulTPEt_vs_TPEt[2][selectIPhis[iIPhi]] = makeTH2F(histName,50,0.,100.,50,0.,100.);
  };
  TH1F * h_lumiSection = makeTH1F("h_lumiSection",497,0.5,497.5);  

  //--------------------------------------------------------------------------------
  // Loop
  //--------------------------------------------------------------------------------
  int lumiSectionIndex;
  for (int i = 0; i < n_events; ++i){
    
    tuple_tree -> GetEntry(i);
    if ( (i + 1) % 10000 == 0 ) std::cout << "Processing event " << i + 1 << "/" << n_events << std::endl;
    
    //-----------------------------------------------------------------
    // Collections of Hcal Trigger Primitive 
    //-----------------------------------------------------------------
    int lumiSection = tuple_tree -> ls;

    h_lumiSection -> Fill(lumiSection);
    if (lumiSection < 400){
      lumiSectionIndex = 1;
    } else {
      lumiSectionIndex = 2;
    };

    CollectionPtr hcalTPs (new Collection(*tuple_tree, tuple_tree -> HcalTriggerPrimitiveIEta -> size()));
    CollectionPtr hcalEmulTPs (new Collection(*tuple_tree, tuple_tree -> HcalEmulTriggerPrimitiveIEta -> size()));


    int nHcalTPs = hcalTPs -> GetSize();
    int nHcalEmulTPs = hcalEmulTPs -> GetSize();
    for (int iHcalTP = 0; iHcalTP < nHcalTPs; ++iHcalTP){
       HcalTP hcalTP = hcalTPs -> GetConstituent<HcalTP>(iHcalTP);
       if( std::find( selectIPhis.begin() , selectIPhis.end() , hcalTP.iphi() ) == selectIPhis.end() ) continue;
       for (int iHcalEmulTP = 0; iHcalEmulTP  < nHcalEmulTPs; ++iHcalEmulTP){
         HcalEmulTP hcalEmulTP = hcalEmulTPs -> GetConstituent<HcalEmulTP>(iHcalEmulTP);
         if ( (hcalEmulTP.ieta() == hcalTP.ieta() && (hcalEmulTP.iphi() == hcalTP.iphi()) ) ){
	   h_emulTPEt_vs_TPEt[lumiSectionIndex][hcalTP.iphi()] -> Fill(hcalEmulTP.Et(),hcalTP.Et());
	 };	 
       };
    };
  };
};
