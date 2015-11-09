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
  // Histograms
  //--------------------------------------------------------------------------------

  //TH1F * recHitTiming = makeTH1F("RecTiming",400,-200,200.);
  TH1F * recHitEnergy = makeTH1F("Energy",30,0,1000.);
  recHitEnergy -> SetTitle(" ; Rechit Energy [GeV] ; ");

  TH2F * occupancy_ts3 = makeTH2F("occupancy_ts3",81,-40.5,40.5,72,0.5,72.5);
  occupancy_ts3 -> SetTitle(" Weighted with TS3 ; i#eta ; i#phi ");

  TH2F * occupancy_ts4 = makeTH2F("occupancy_ts4",81,-40.5,40.5,72,0.5,72.5);
  occupancy_ts4 -> SetTitle(" Weighted with TS4 ; i#eta ; i#phi ");

  TH2F * noOfDigiHit = makeTH2F("noOfDigiHit",81,-40.5,40.5,72,0.5,72.5);
  noOfDigiHit -> SetTitle(" Weighted with 1 (Counting the number of digi only) ; i#eta ; i#phi ");

  TH1F * ts3_Div_ts3ts5 = makeTH1F("ts3_Div_ts3ts5",30,0.,1.);
  ts3_Div_ts3ts5 -> SetTitle(" ; TS3/(TS3+TS5) ; ");

  TH2F * recHitEnergy_ts3_Div_ts3ts5 = makeTH2F("recHitEnergy_ts3_Div_ts3ts5",30,0,1000.,30,0.,1.);
  recHitEnergy_ts3_Div_ts3ts5 -> SetTitle(" ; Rechit Energy [GeV] ; TS3/(TS3+TS5) ");

  TH2F * ieta_ts3_Div_ts3ts5 = makeTH2F("ieta_ts3_Div_ts3ts5",81,-40.5,40.5,30,0.,1.);
  ieta_ts3_Div_ts3ts5 -> SetTitle(" ; i#eta ; TS3/(TS3+TS5) ");

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
      // recHitTiming -> Fill( hbheDigi.recHitTime() );
      
      double ieta = hbheDigi.ieta();
      double iphi = hbheDigi.iphi();
      double energy = hbheDigi.energy();
      double fc_TS3 = hbheDigi.fc(3);
      double fc_TS4 = hbheDigi.fc(4);
      double fc_TS5 = hbheDigi.fc(5);

      recHitEnergy -> Fill( hbheDigi.energy() );
      occupancy_ts3 -> Fill( ieta , iphi , fc_TS3 );
      occupancy_ts4 -> Fill( ieta , iphi , fc_TS4 );
      noOfDigiHit -> Fill( ieta , iphi );
      ts3_Div_ts3ts5 -> Fill( fc_TS3/(fc_TS3+fc_TS5) );
      recHitEnergy_ts3_Div_ts3ts5 -> Fill( energy , fc_TS3/(fc_TS3+fc_TS5) );
      ieta_ts3_Div_ts3ts5 -> Fill( ieta , fc_TS3/(fc_TS3+fc_TS5)  );

    };
  };
  
  // occupancy_ts3 -> Scale( (double) 1/tuple_tree -> HBHEDigiIEta -> size() );
  // occupancy_ts4 -> Scale( (double) 1/tuple_tree -> HBHEDigiIEta -> size() );
}
