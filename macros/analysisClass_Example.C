#include "analysisClass.h"
#include "HcalTupleTree.h"
#include "HBHEDigi.h"

void analysisClass::loop(){

  //--------------------------------------------------------------------------------
  // Configurables
  //--------------------------------------------------------------------------------
  const double recHitEnergyCut = 0.;
  
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
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiIEta"      , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiIPhi"      , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiSize"      , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiRecEnergy" , kTRUE);

  //--------------------------------------------------------------------------------
  // Histograms
  //--------------------------------------------------------------------------------

  TH1F * h_recHitEnergy = makeTH1F("Energy",50,0,100.);
  h_recHitEnergy -> SetTitle(" ; Rechit Energy [GeV] ; ");

  //--------------------------------------------------------------------------------
  // Loop
  //--------------------------------------------------------------------------------
  int nHBHEDigis;

  for (int i = 0; i < n_events; ++i){
    
    tuple_tree -> GetEntry(i);
    if ( (i + 1) % 10000 == 0 ) std::cout << "Processing event " << i + 1 << "/" << n_events << std::endl;

    CollectionPtr hbheDigis (new Collection(*tuple_tree, tuple_tree -> HBHEDigiIEta -> size()));
    
    nHBHEDigis = hbheDigis -> GetSize();

    for (int iHBHEDigi = 0; iHBHEDigi < nHBHEDigis; ++iHBHEDigi){
      HBHEDigi hbheDigi = hbheDigis -> GetConstituent<HBHEDigi>(iHBHEDigi);

      if (hbheDigi.energy() < recHitEnergyCut) continue;

      h_recHitEnergy -> Fill( hbheDigi.energy() );

    };
  };  
}
  
