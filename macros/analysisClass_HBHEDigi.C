#include "analysisClass.h"
#include "HcalTupleTree.h"
#include "HBHEDigi.h"

void analysisClass::loop(){

  //--------------------------------------------------------------------------------
  // Configurables
  //--------------------------------------------------------------------------------
  const double recHitEnergyCut = 5.;
  
  //--------------------------------------------------------------------------------
  // Declare HCAL tree(s)
  //--------------------------------------------------------------------------------

  HcalTupleTree * tuple_tree = getTree<HcalTupleTree>("skim_tree");
  int n_events = tuple_tree -> fChain -> GetEntries();
  std::cout << "n events = " << n_events << std::endl;
  
  //--------------------------------------------------------------------------------
  // Turn on/off branches
  //--------------------------------------------------------------------------------
  
  tuple_tree -> fChain -> SetBranchStatus("*"               , kFALSE);
  tuple_tree -> fChain -> SetBranchStatus("run"             , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("event"           , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("ls"              , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiFC"        , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiIEta"      , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiIPhi"      , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiSize"      , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiRecEnergy" , kTRUE);
  
  //--------------------------------------------------------------------------------
  // Loop
  //--------------------------------------------------------------------------------
  int nHBHEDigis;

  TH1F * recHitTiming = makeTH1F("RecTiming",400,-200,200.);
  TH1F * recHitEnergy = makeTH1F("Energy",100,0,10.);
  TH2F * occupancy_ts3 = makeTH2F("occupancy_ts3",81,-40.5,40.5,72,0.5,72.5);
  TH2F * occupancy_ts4 = makeTH2F("occupancy_ts4",81,-40.5,40.5,72,0.5,72.5);
  TH2F * noOfDigiHit = makeTH2F("noOfDigiHit",81,-40.5,40.5,72,0.5,72.5);

  for (int i = 0; i < n_events; ++i){
    
    tuple_tree -> GetEntry(i);
    if ( (i + 1) % 10000 == 0 ) std::cout << "Processing event " << i + 1 << "/" << n_events << std::endl;

    CollectionPtr hbheDigis (new Collection(*tuple_tree, tuple_tree -> HBHEDigiIEta -> size()));
    
    nHBHEDigis = hbheDigis -> GetSize();

    for (int iHBHEDigi = 0; iHBHEDigi < nHBHEDigis; ++iHBHEDigi){
      HBHEDigi hbheDigi = hbheDigis -> GetConstituent<HBHEDigi>(iHBHEDigi);

      if (hbheDigi.energy() < recHitEnergyCut) continue;
      // recHitTiming -> Fill( hbheDigi.recHitTime() );
      recHitEnergy -> Fill( hbheDigi.energy() );
      occupancy_ts3 -> Fill( hbheDigi.ieta() , hbheDigi.iphi() , hbheDigi.fc(3) );
      occupancy_ts4 -> Fill( hbheDigi.ieta() , hbheDigi.iphi() , hbheDigi.fc(4) );
      noOfDigiHit -> Fill( hbheDigi.ieta() , hbheDigi.iphi() );

    };
  };
  
  // occupancy_ts3 -> Scale( (double) 1/tuple_tree -> HBHEDigiIEta -> size() );
  // occupancy_ts4 -> Scale( (double) 1/tuple_tree -> HBHEDigiIEta -> size() );
}
