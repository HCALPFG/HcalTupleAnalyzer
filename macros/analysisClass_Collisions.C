#include "analysisClass.h"
#include "HcalTupleTree.h"
#include "HBHEDigi.h"
#include "HFDigi.h"
#include "HODigi.h"
#include "RBXMap.h"
#include <fstream>


void analysisClass::loop(){
  
  //--------------------------------------------------------------------------------
  // Declare HCAL tree(s)
  //--------------------------------------------------------------------------------

  HcalTupleTree * tuple_tree = getTree<HcalTupleTree>("tuple_tree");
  int n_events = tuple_tree -> fChain -> GetEntries();
  std::cout << "n events = " << n_events << std::endl;

  //--------------------------------------------------------------------------------
  // RBX map
  //--------------------------------------------------------------------------------
  
  RBXMap map;
  map.LoadFile ( "data/emaps/HCALmapHBEF_E.txt" );
  map.LoadFile ( "data/emaps/HCALmapHO_G.txt" );
  
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

  TH1F * h_energy = makeTH1F( "energy", 1000, 0, 50);
  TH1F * h_time = makeTH1F( "time", 200, -100, 100);
  TH2F * h_time_vs_energy = makeTH2F( "time_vs_energy", 100, -20, 20, 100, -5, 45);
  TH2F * h_eta_vs_phi = makeTH2F("eta_vs_phi",100,-5.,5., 100, -3.14, 3.14 );
  TH2F * h_ieta_vs_iphi =  makeTH2F("ieta_vs_iphi",81, -40.5, 40.5,72,0.5,72.5);

  TH2F * h_ieta_vs_iphi_TSRatio = makeTH2F("ieta_vs_iphi_TSRatio",81, -40.5, 40.5,72,0.5,72.5);
  TH2F * h_ieta_vs_iphi_TSRatioCount = makeTH2F("ieta_vs_iphi_TSRatioCount",81, -40.5, 40.5,72,0.5,72.5);

  std::vector<TH2F*> h_occupancy (5);
  std::vector<TH2F*> h_averageTime (5);


  char hist_name[100];
  for (int i = 1; i <=4; ++i){
    sprintf(hist_name,"occupancy_depth%d", i);
    h_occupancy[i] = makeTH2F(hist_name, 85, -42.5, 42.5, 72, 0.5, 72.5 );

    sprintf(hist_name,"ieta_vs_iphi_averageTime_depth%d",i);
    h_averageTime[i] = makeTH2F(hist_name, 85, -42.5, 42.5, 72, 0.5, 72.5 );
  }


  //--------------------------------------------------------------------------------
  // Special Validation Plot
  //--------------------------------------------------------------------------------
  TH2F * h_ieta_vs_iphi_TimingCut = makeTH2F("ieta_vs_iphi_TimingCut",81,-40.5,40.5,72,0.5,72.5);
  TH2F * h_eta_vs_phi_TimingCut = makeTH2F("eta_vs_phi_TimingCut",100,-5.,5., 100, -3.14, 3.14 );


  //--------------------------------------------------------------------------------
  // Loop
  //--------------------------------------------------------------------------------
  
  for (int i = 0; i < n_events; ++i){
    
    tuple_tree -> GetEntry(i);
    if ( (i + 1) % 1000 == 0 ) std::cout << "Processing event " << i + 1 << "/" << n_events << std::endl;
    
    //-----------------------------------------------------------------
    // Collections of HBHE, HF, HO digis
    //-----------------------------------------------------------------
    CollectionPtr hbheDigis (new Collection(*tuple_tree, tuple_tree -> HBHEDigiIEta -> size()));
    
    int nHBHEDigis = hbheDigis -> GetSize();
    for (int iHBHEDigi = 0; iHBHEDigi < nHBHEDigis; ++iHBHEDigi){
      HBHEDigi hbheDigi = hbheDigis -> GetConstituent<HBHEDigi>(iHBHEDigi);

      if ( hbheDigi.energy() < 5.0 ) continue;

      h_occupancy[hbheDigi.depth()] -> Fill(hbheDigi.ieta(), hbheDigi.iphi());
      
      h_energy -> Fill ( hbheDigi.energy() );
      h_time   -> Fill ( hbheDigi.recHitTime());
      h_time_vs_energy -> Fill ( hbheDigi.recHitTime(), hbheDigi.energy());
      h_eta_vs_phi->Fill(hbheDigi.eta(),hbheDigi.phi());
      h_ieta_vs_iphi->Fill(hbheDigi.ieta(),hbheDigi.iphi());

      // Fiddling with samples
      // std::cout << hbheDigi.size() << std::endl;
      // if ((hbheDigi.adc(4) > 30) && (hbheDigi.adc(4) < 100)){
      //  h_ieta_vs_iphi_TSRatio -> Fill(hbheDigi.ieta(),hbheDigi.iphi(),hbheDigi.adc(5)/hbheDigi.adc(4));
      //  h_ieta_vs_iphi_TSRatioCount -> Fill(hbheDigi.ieta(),hbheDigi.iphi());
      //};


      //-----------------------------------------------------------------
      // Filling of special validation plot
      //-----------------------------------------------------------------
      if (hbheDigi.recHitTime() > 10.){
        h_ieta_vs_iphi_TimingCut -> Fill(hbheDigi.ieta(),hbheDigi.iphi());
        h_eta_vs_phi_TimingCut -> Fill(hbheDigi.eta(),hbheDigi.phi());
      };
    };
  };
  
  
  // h_ieta_vs_iphi_TSRatio -> Divide(h_ieta_vs_iphi_TSRatioCount);

};
