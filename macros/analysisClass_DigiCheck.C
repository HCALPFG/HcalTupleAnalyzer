#include "analysisClass.h"
#include "HcalTupleTree.h"
#include "HBHEDigi.h"
#include "HFDigi.h"
#include "RBXMap.h"

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
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiEta", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiPhi", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiRecEnergy", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiRecTime", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiAllFC", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiEnergy", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiFC", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiGain", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiNomFC", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiPedFC", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiRCGain", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiDepth", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiFiberIdleOffset", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiIEta", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiIPhi", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiPresamples", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiSize", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiADC", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiCapID", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiDV", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiER", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiFiber", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiFiberChan", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiRaw", kTRUE);

  tuple_tree -> fChain -> SetBranchStatus("HFDigiEta", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiPhi", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiRecEnergy", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiRecTime", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiAllFC", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiEnergy", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiFC", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiGain", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiNomFC", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiPedFC", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiRCGain", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiDepth", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiFiberIdleOffset", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiIEta", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiIPhi", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiPresamples", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiSize", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiADC", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiCapID", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiDV", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiER", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiFiber", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiFiberChan", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiRaw", kTRUE);
  
  //--------------------------------------------------------------------------------
  // Declare and load RBX map
  //--------------------------------------------------------------------------------

  RBXMap map;
  map.LoadFile ( "data/emaps/HCALmapHBEF_E.txt" );
  map.LoadFile ( "data/emaps/HCALmapHO_E.txt" );

  //--------------------------------------------------------------------------------
  // Make histograms
  //--------------------------------------------------------------------------------

  TH2F * h_hbhe_occupancy_NDV = makeTH2F ("hbhe_occupancy_NDV", 85, -42.5, 42.5, 72, 0.5, 72.5 );
  TH2F * h_hbhe_occupancy_ER  = makeTH2F ("hbhe_occupancy_ER" , 85, -42.5, 42.5, 72, 0.5, 72.5 );
  TH2F * h_hbhe_occupancy_CAP = makeTH2F ("hbhe_occupancy_CAP", 85, -42.5, 42.5, 72, 0.5, 72.5 );
  TH1F * h_hbhe_nNDV_perEvent = makeTH1F ("hbhe_nNDV_perEvent", n_events, -0.5, float(n_events - 0.5));
  TH1F * h_hbhe_nER_perEvent  = makeTH1F ("hbhe_nER_perEvent" , n_events, -0.5, float(n_events - 0.5));
  TH1F * h_hbhe_nCAP_perEvent = makeTH1F ("hbhe_nCAP_perEvent", n_events, -0.5, float(n_events - 0.5));

  TH2F * h_hf_occupancy_NDV = makeTH2F ("hf_occupancy_NDV", 85, -42.5, 42.5, 72, 0.5, 72.5 );
  TH2F * h_hf_occupancy_ER  = makeTH2F ("hf_occupancy_ER" , 85, -42.5, 42.5, 72, 0.5, 72.5 );
  TH2F * h_hf_occupancy_CAP = makeTH2F ("hf_occupancy_CAP", 85, -42.5, 42.5, 72, 0.5, 72.5 );
  TH1F * h_hf_nNDV_perEvent = makeTH1F ("hf_nNDV_perEvent", n_events, -0.5, float(n_events - 0.5));
  TH1F * h_hf_nER_perEvent  = makeTH1F ("hf_nER_perEvent" , n_events, -0.5, float(n_events - 0.5));
  TH1F * h_hf_nCAP_perEvent = makeTH1F ("hf_nCAP_perEvent", n_events, -0.5, float(n_events - 0.5));

  TH2F * vh_hbhe_occupancy_NDV[5];
  TH2F * vh_hbhe_occupancy_ER [5];
  TH2F * vh_hbhe_occupancy_CAP[5];

  TH2F * vh_hf_occupancy_NDV[3];
  TH2F * vh_hf_occupancy_ER [3];
  TH2F * vh_hf_occupancy_CAP[3];

  char hist_name[100];

  for (int i = 1; i <= 4; ++i){
    sprintf(hist_name, "hbhe_occupancy_NDV_depth%d", i );
    vh_hbhe_occupancy_NDV[i] = makeTH2F ( hist_name, 85, -42.5, 42.5, 72, 0.5, 72.5 );

    sprintf(hist_name, "hbhe_occupancy_ER_depth%d", i );
    vh_hbhe_occupancy_ER[i] = makeTH2F ( hist_name, 85, -42.5, 42.5, 72, 0.5, 72.5 );
    
    sprintf(hist_name, "hbhe_occupancy_CAP_depth%d", i );
    vh_hbhe_occupancy_CAP[i] = makeTH2F ( hist_name, 85, -42.5, 42.5, 72, 0.5, 72.5 );
  }

  for (int i = 1; i <= 2; ++i){
    sprintf(hist_name, "hf_occupancy_NDV_depth%d", i );
    vh_hf_occupancy_NDV[i] = makeTH2F ( hist_name, 85, -42.5, 42.5, 72, 0.5, 72.5 );

    sprintf(hist_name, "hf_occupancy_ER_depth%d", i );
    vh_hf_occupancy_ER[i] = makeTH2F ( hist_name, 85, -42.5, 42.5, 72, 0.5, 72.5 );
    
    sprintf(hist_name, "hf_occupancy_CAP_depth%d", i );
    vh_hf_occupancy_CAP[i] = makeTH2F ( hist_name, 85, -42.5, 42.5, 72, 0.5, 72.5 );
  }

  
  //--------------------------------------------------------------------------------
  // Loop
  //--------------------------------------------------------------------------------

  for (int i = 0; i < n_events; ++i){
    
    tuple_tree -> GetEntry(i);
    if ( (i + 1) % 100 == 0 ) std::cout << "Processing event " << i + 1 << "/" << n_events << std::endl;

    CollectionPtr hbheDigis (new Collection(*tuple_tree, tuple_tree -> HBHEDigiIEta -> size()));
    CollectionPtr hbheDigis_ndv = hbheDigis -> SkimByID<HBHEDigi>(DIGI_HAS_NDV);
    CollectionPtr hbheDigis_er  = hbheDigis -> SkimByID<HBHEDigi>(DIGI_HAS_ER);
    CollectionPtr hbheDigis_cap = hbheDigis -> SkimByID<HBHEDigi>(DIGI_HAS_CAPID_ERR);
    
    CollectionPtr hfDigis (new Collection(*tuple_tree, tuple_tree -> HFDigiIEta -> size()));
    CollectionPtr hfDigis_ndv = hfDigis -> SkimByID<HFDigi>(DIGI_HAS_NDV);
    CollectionPtr hfDigis_er  = hfDigis -> SkimByID<HFDigi>(DIGI_HAS_ER);
    CollectionPtr hfDigis_cap = hfDigis -> SkimByID<HFDigi>(DIGI_HAS_CAPID_ERR);
    
    int bin = h_hbhe_nNDV_perEvent -> FindBin(i);
    
    int nHBHEDigis_NDV = hbheDigis_ndv -> GetSize();
    for (int iHBHEDigi = 0; iHBHEDigi < nHBHEDigis_NDV; ++iHBHEDigi){
      HBHEDigi hbheDigi = hbheDigis_ndv -> GetConstituent<HBHEDigi>(iHBHEDigi);
      h_hbhe_occupancy_NDV -> Fill (  hbheDigi.ieta(), hbheDigi.iphi ());
      vh_hbhe_occupancy_NDV[hbheDigi.depth()] -> Fill (  hbheDigi.ieta(), hbheDigi.iphi ());
    }
    h_hbhe_nNDV_perEvent -> SetBinContent(bin, nHBHEDigis_NDV);
    
    int nHBHEDigis_ER = hbheDigis_er -> GetSize();
    for (int iHBHEDigi = 0; iHBHEDigi < nHBHEDigis_ER; ++iHBHEDigi){
      HBHEDigi hbheDigi = hbheDigis_er -> GetConstituent<HBHEDigi>(iHBHEDigi);
      h_hbhe_occupancy_ER -> Fill (  hbheDigi.ieta(), hbheDigi.iphi ());
      vh_hbhe_occupancy_ER[hbheDigi.depth()] -> Fill (  hbheDigi.ieta(), hbheDigi.iphi ());
    }
    h_hbhe_nER_perEvent -> SetBinContent(bin, nHBHEDigis_ER);
    
    int nHBHEDigis_CAP = hbheDigis_cap -> GetSize();
    for (int iHBHEDigi = 0; iHBHEDigi < nHBHEDigis_CAP; ++iHBHEDigi){
      HBHEDigi hbheDigi = hbheDigis_cap -> GetConstituent<HBHEDigi>(iHBHEDigi);
      h_hbhe_occupancy_CAP -> Fill (  hbheDigi.ieta(), hbheDigi.iphi ());
      vh_hbhe_occupancy_CAP[hbheDigi.depth()] -> Fill (  hbheDigi.ieta(), hbheDigi.iphi ());
    }
    h_hbhe_nCAP_perEvent -> SetBinContent(bin, nHBHEDigis_CAP);


    int nHFDigis_NDV = hfDigis_ndv -> GetSize();
    for (int iHFDigi = 0; iHFDigi < nHFDigis_NDV; ++iHFDigi){
      HFDigi hfDigi = hfDigis_ndv -> GetConstituent<HFDigi>(iHFDigi);
      h_hf_occupancy_NDV -> Fill (  hfDigi.ieta(), hfDigi.iphi ());
      vh_hf_occupancy_NDV[hfDigi.depth()] -> Fill (  hfDigi.ieta(), hfDigi.iphi ());
    }
    h_hf_nNDV_perEvent -> SetBinContent(bin, nHFDigis_NDV);
    
    int nHFDigis_ER = hfDigis_er -> GetSize();
    for (int iHFDigi = 0; iHFDigi < nHFDigis_ER; ++iHFDigi){
      HFDigi hfDigi = hfDigis_er -> GetConstituent<HFDigi>(iHFDigi);
      h_hf_occupancy_ER -> Fill (  hfDigi.ieta(), hfDigi.iphi ());
      vh_hf_occupancy_ER[hfDigi.depth()] -> Fill (  hfDigi.ieta(), hfDigi.iphi ());
    }
    h_hf_nER_perEvent -> SetBinContent(bin, nHFDigis_ER);
    
    int nHFDigis_CAP = hfDigis_cap -> GetSize();
    for (int iHFDigi = 0; iHFDigi < nHFDigis_CAP; ++iHFDigi){
      HFDigi hfDigi = hfDigis_cap -> GetConstituent<HFDigi>(iHFDigi);
      h_hf_occupancy_CAP -> Fill (  hfDigi.ieta(), hfDigi.iphi ());
      vh_hf_occupancy_CAP[hfDigi.depth()] -> Fill (  hfDigi.ieta(), hfDigi.iphi ());
    }
    h_hf_nCAP_perEvent -> SetBinContent(bin, nHFDigis_CAP);


    if ( nHBHEDigis_NDV > 0 ||
	 nHBHEDigis_ER  > 0 ||
	 nHBHEDigis_CAP > 0 ){
      std::cout 
	<< "run = " << tuple_tree -> run << ", "
	<< "event = " << tuple_tree -> event << ", "
	<< "ls = " << tuple_tree -> ls << ", "
	<< "nNDV = "  << nHBHEDigis_NDV << ", "
	<< "nER = "   << nHBHEDigis_ER  << ", "
	<< "nCAP = "  << nHBHEDigis_CAP << std::endl;
    }
    
  }
}
