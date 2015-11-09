#include "analysisClass.h"
#include "HcalTupleTree.h"
#include "HBHEDigi.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>

void analysisClass::loop(){
 
  //--------------------------------------------------------------------------------
  // Configurables
  //--------------------------------------------------------------------------------
 
  //--------------------------------------------------------------------------------
  // Declare HCAL tree(s)
  //--------------------------------------------------------------------------------

  HcalTupleTree * tuple_tree = getTree<HcalTupleTree>("skim_tree");
  int n_events = tuple_tree -> fChain -> GetEntries();
  std::cout << "n events = " << n_events << std::endl;
  
  //--------------------------------------------------------------------------------
  // Turn on/off branches
  //--------------------------------------------------------------------------------
  
  tuple_tree -> fChain -> SetBranchStatus("*", kFALSE);
  tuple_tree -> fChain -> SetBranchStatus("run", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("event", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("ls", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiRecEnergy", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiIEta", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiIPhi", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiFC", kTRUE);

  //--------------------------------------------------------------------------------
  // Make histograms
  //--------------------------------------------------------------------------------
  char histName[100];
  char title[100];

  //--------------------------------------------------------------------------------
  // Necessary Variables
  //--------------------------------------------------------------------------------

  //--------------------------------------------------------------------------------
  // Loop
  //--------------------------------------------------------------------------------
  
  for (int i = 0; i < n_events; ++i){
    
    tuple_tree -> GetEntry(i);
    if ( (i + 1) % 10000 == 0 ) std::cout << "Processing event " << i + 1 << "/" << n_events << std::endl;

    //-----------------------------------------------------------------
    // Select Event
    //-----------------------------------------------------------------
    int runNumber = tuple_tree -> run;
    int lumiSection = tuple_tree -> ls;
    int eventNumber = tuple_tree -> event;

    //-----------------------------------------------------------------
    // Collections of HBHE
    //-----------------------------------------------------------------
    CollectionPtr hbheDigis (new Collection(*tuple_tree, tuple_tree -> HBHEDigiIEta -> size()));
    
    int nHBHEDigis = hbheDigis -> GetSize();
    int count = 0; int count3 = 0;
    for (int iHBHEDigi = 0; iHBHEDigi < nHBHEDigis; ++iHBHEDigi){
      HBHEDigi hbheDigi = hbheDigis -> GetConstituent<HBHEDigi>(iHBHEDigi);

      if ( hbheDigi.energy() < 5.0 ) continue;

      if ( abs(hbheDigi.ieta()) > 12 ) continue;

      if ( hbheDigi.fc(3) < 50 ) continue;

      sprintf(histName,"PulseShape_%d_%d_%d_%d",runNumber,lumiSection,eventNumber,iHBHEDigi);
      sprintf(title," %d %d %d %d  ; TS ; FC",runNumber,lumiSection,eventNumber,iHBHEDigi);
      TH1F * tempHist = makeTH1F(histName,10,-0.5,9.5);
      tempHist -> SetTitle(title);
      for (int its = 0; its != 10; its++){
        tempHist -> Fill ( its , hbheDigi.fc(its) );
      };
    };
  };
};
