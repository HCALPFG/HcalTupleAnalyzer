#include "analysisClass.h"
#include "HcalTupleTree.h"
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
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiRecEnergy", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiRecTime", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiIEta", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiIPhi", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiEta", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiPhi", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiDepth", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiSubdet", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiRawID", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiADC", kTRUE);

  //--------------------------------------------------------------------------------
  // Make histograms
  //--------------------------------------------------------------------------------
  std::vector<int> runList = {255981,256001,256141,256166,256171,256216,256236,256346,256406,256446,256461};
  std::map<int,TH2F*> RecHitTiming;
  std::map<int,TH2F*> Occupancy;
  
  char histName[100];
  for (std::vector<int>::iterator itr = runList.begin(); itr != runList.end(); itr++){
    sprintf(histName,"AverageRecHitTime_%d",*itr);
    RecHitTiming[*itr] = makeTH2F(histName,81, -40.5, 40.5,72,0.5,72.5);
    sprintf(histName,"Occupancy_%d",*itr);
    Occupancy[*itr] = makeTH2F(histName,81, -40.5, 40.5,72,0.5,72.5);
  };

  //--------------------------------------------------------------------------------
  // Loop
  //--------------------------------------------------------------------------------
  
  for (int i = 0; i < n_events; ++i){
    
    tuple_tree -> GetEntry(i);
    if ( (i + 1) % 1000 == 0 ) std::cout << "Processing event " << i + 1 << "/" << n_events << std::endl;
    
    //-----------------------------------------------------------------
    // Collections of HBHE
    //-----------------------------------------------------------------
    CollectionPtr hbheDigis (new Collection(*tuple_tree, tuple_tree -> HBHEDigiIEta -> size()));
    
    int runNumber = tuple_tree -> run;
    int nHBHEDigis = hbheDigis -> GetSize();
    for (int iHBHEDigi = 0; iHBHEDigi < nHBHEDigis; ++iHBHEDigi){
      HBHEDigi hbheDigi = hbheDigis -> GetConstituent<HBHEDigi>(iHBHEDigi);

      if ( hbheDigi.energy() < 5.0 ) continue;
      RecHitTiming[runNumber] -> Fill(hbheDigi.ieta(),hbheDigi.iphi(),hbheDigi.recHitTime());
      Occupancy[runNumber] -> Fill(hbheDigi.ieta(),hbheDigi.iphi());
 
    };
  };

  TGraph * graph = makeTGraph();
  char binLabel[100];
  int iBin = 1;
  for (std::map<int,TH2F*>::iterator it = RecHitTiming.begin(); it != RecHitTiming.end(); it++){
    // graph -> SetPoint((int)(it-RecHitTiming.begin()+1), it -> first, it -> second -> Integral() / Occupancy[it -> first] -> Integral());
    graph -> SetPoint( iBin , it -> first , it -> second -> Integral() / Occupancy[it -> first] -> Integral());
    sprintf(binLabel,"%d",it -> first);
    graph -> GetXaxis() -> SetBinLabel( iBin , binLabel);
  };
   

};
