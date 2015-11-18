#include "analysisClass.h"
#include "HcalTupleTree.h"
#include "HBHEDigi.h"
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
  tuple_tree -> fChain -> SetBranchStatus("HFDigiIEta"      , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiIPhi"      , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiRecEnergy" , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiFC"        , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiIEta"      , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiIPhi"      , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiRecEnergy" , kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiRecTime"   , kTRUE);

  
  //--------------------------------------------------------------------------------
  // Loop
  //--------------------------------------------------------------------------------
  int nHBHEDigis;
  std::map<int,TH2F*> hbhe_occupancy;
  hbhe_occupancy[1] = makeTH2F("hbhe_occupancy_1", 81, -40.5, 40.5,72,0.5,72.5);
  hbhe_occupancy[1] -> SetTitle("Lumi Section < 400 ; i#eta ; i#phi ");
  hbhe_occupancy[2] = makeTH2F("hbhe_occupancy_2", 81, -40.5, 40.5,72,0.5,72.5);
  hbhe_occupancy[2] -> SetTitle("Lumi Section > 400 ; i#eta ; i#phi ");

  // std::map<int,TH1F*> hbhe_signal;
  // hbhe_signal[1] = makeTH1F("hbhe_signal_1", 10 , -0.5, 9.5 );
  // hbhe_signal[1] -> SetTitle("Signal Shape, Lumi Section < 400 ; TS ; fC");
  // hbhe_signal[2] = makeTH1F("hbhe_signal_2", 10 , -0.5, 9.5 );
  // hbhe_signal[2] -> SetTitle("Signal Shape, Lumi Section > 400 ; TS ; fC");

  int nHFDigis;
  std::map<int,TH2F*> hf_occupancy;
  hf_occupancy[1] = makeTH2F("hf_occupancy_1", 81, -40.5, 40.5,72,0.5,72.5);
  hf_occupancy[1] -> SetTitle("Lumi Section < 400 ; i#eta ; i#phi ");
  hf_occupancy[2] = makeTH2F("hf_occupancy_2", 81, -40.5, 40.5,72,0.5,72.5);
  hf_occupancy[2] -> SetTitle("Lumi Section > 400 ; i#eta ; i#phi ");

  std::map<int,TH1F*> hf21_signal;
  hf21_signal[1] = makeTH1F("hf21_signal_1", 4 , -0.5, 3.5 );
  hf21_signal[1] -> SetTitle("Signal Shape, i#phi = 21, Lumi Section < 400 ; TS ; fC");
  hf21_signal[2] = makeTH1F("hf21_signal_2", 4 , -0.5, 3.5 );
  hf21_signal[2] -> SetTitle("Signal Shape, i#phi = 21, Lumi Section > 400 ; TS ; fC");
  std::map<int,TH1F*> hf23_signal;
  hf23_signal[1] = makeTH1F("hf23_signal_1", 4 , -0.5, 3.5 );
  hf23_signal[1] -> SetTitle("Signal Shape, i#phi = 23, Lumi Section < 400 ; TS ; fC");
  hf23_signal[2] = makeTH1F("hf23_signal_2", 4 , -0.5, 3.5 );
  hf23_signal[2] -> SetTitle("Signal Shape, i#phi = 23, Lumi Section > 400 ; TS ; fC");

  int lumiSection,lumiIndex;

  for (int i = 0; i < n_events; ++i){
    
    tuple_tree -> GetEntry(i);
    if ( (i + 1) % 10000 == 0 ) std::cout << "Processing event " << i + 1 << "/" << n_events << std::endl;

    if ( not ( (i + 1) % 1000 == 0 ) ) continue;

    lumiSection = tuple_tree -> ls;
    if (lumiSection < 400){
      lumiIndex = 1;
    } else {
      lumiIndex = 2;
    };

    // Dealing with HBHEDigis
    CollectionPtr hbheDigis (new Collection(*tuple_tree, tuple_tree -> HBHEDigiIEta -> size()));
    nHBHEDigis = hbheDigis -> GetSize();
    for (int iHBHEDigi = 0; iHBHEDigi < nHBHEDigis; ++iHBHEDigi){
      HBHEDigi hbheDigi = hbheDigis -> GetConstituent<HBHEDigi>(iHBHEDigi);

      if (hbheDigi.energy() < 5) continue;
      hbhe_occupancy[lumiIndex] -> Fill( hbheDigi.ieta() , hbheDigi.iphi() );
      // for (int iTS = 0; iTS != 10; iTS++){
      //   hbhe_signal[lumiIndex] -> Fill( iTS , hbheDigi.fc(iTS) );
      // };
    }; 

    // Dealing with HFDigis
    CollectionPtr hfDigis (new Collection(*tuple_tree, tuple_tree -> HFDigiIEta -> size()));
    nHFDigis = hfDigis -> GetSize();
    for (int iHFDigi = 0; iHFDigi < nHFDigis; ++iHFDigi){
      HFDigi hfDigi = hfDigis -> GetConstituent<HFDigi>(iHFDigi);

      if (hfDigi.energy() < 5) continue;
      hf_occupancy[lumiIndex] -> Fill( hfDigi.ieta() , hfDigi.iphi() );
      // if ((hfDigi.iphi() != 21) || (hfDigi.iphi() != 23)) continue;
      if (hfDigi.iphi() == 21){
        for (int iTS = 0; iTS != 4; iTS++){
          hf21_signal[lumiIndex] -> Fill( iTS , hfDigi.fc(iTS) );
        };
      };
      if (hfDigi.iphi() == 23){
        for (int iTS = 0; iTS != 4; iTS++){
          hf23_signal[lumiIndex] -> Fill( iTS , hfDigi.fc(iTS) );
        };
      };
    };
  };
}
