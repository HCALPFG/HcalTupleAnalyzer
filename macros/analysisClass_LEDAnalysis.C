#include "analysisClass.h"
#include "HcalTupleTree.h"
#include "HODigi.h"
#include "RBXMap.h"
#include "TH2F.h"

const int n_ho_channels = 2160;

void analysisClass::loop(){
  
  //--------------------------------------------------------------------------------
  // Declare HCAL tree(s)
  //--------------------------------------------------------------------------------

  HcalTupleTree * tuple_tree = getTree<HcalTupleTree>("tuple_tree");
  int n_events = tuple_tree -> fChain -> GetEntries();

  //--------------------------------------------------------------------------------
  // Turn on/off branches
  //--------------------------------------------------------------------------------
  
  tuple_tree -> fChain -> SetBranchStatus("*"               , kFALSE);
  tuple_tree -> fChain -> SetBranchStatus("run"             , kTRUE );
  tuple_tree -> fChain -> SetBranchStatus("HODigiIEta"      , kTRUE );
  tuple_tree -> fChain -> SetBranchStatus("HODigiIPhi"      , kTRUE );
  tuple_tree -> fChain -> SetBranchStatus("HODigiDepth"     , kTRUE );
  // tuple_tree -> fChain -> SetBranchStatus("HODigiRecEnergy" , kTRUE );
  // tuple_tree -> fChain -> SetBranchStatus("HODigiRecTime"   , kTRUE );
  // tuple_tree -> fChain -> SetBranchStatus("HODigiFC"        , kTRUE );
  tuple_tree -> fChain -> SetBranchStatus("HODigiSize"      , kTRUE );
  // tuple_tree -> fChain -> SetBranchStatus("HODigiGain"      , kTRUE );
  tuple_tree -> fChain -> SetBranchStatus("HODigiADC"      ,  kTRUE );

  //--------------------------------------------------------------------------------
  // Declare and load RBX map
  //--------------------------------------------------------------------------------

  RBXMap map;
  map.LoadFile ( "data/emaps/HCALmapHBEF_E.txt" );
  map.LoadFile ( "data/emaps/HCALmapHO_E.txt" );

  //--------------------------------------------------------------------------------
  // Make histograms
  //--------------------------------------------------------------------------------
  std::map < std::pair<int,int> , TH2F * > adcSum;
  std::map < std::pair<int,int> , TH2F * > count;
  char hist_name[50];

  //--------------------------------------------------------------------------------
  // Loop
  //--------------------------------------------------------------------------------
  for (int i = 0; i < n_events; ++i){ 
    tuple_tree -> GetEntry(i);
    if ( (i + 1) % 100 == 0 ) std::cout << "Processing event " << i + 1 << "/" << n_events << std::endl;

    CollectionPtr hoDigis (new Collection(*tuple_tree, tuple_tree -> HODigiIEta -> size()));

    int nHODigis = hoDigis -> GetSize();
    for (int iHODigi = 0; iHODigi < nHODigis; ++iHODigi){
      HODigi hoDigi = hoDigis -> GetConstituent<HODigi>(iHODigi);

      // Collect values
      int    run    = tuple_tree -> run;
      int    digiSize = hoDigi.size();

      std::pair<int,int> pair = std::make_pair(run,hoDigi.depth());

      if (adcSum.find(pair) == adcSum.end()){
	sprintf(hist_name,"adcSum_%d_%d",run,hoDigi.depth());
        adcSum[pair] = makeTH2F(hist_name,31,-15.5,15.5,72,0.5,72.5);
      };
      if (count.find(pair) == count.end()){
        sprintf(hist_name,"count_%d_%d",run,hoDigi.depth());
        count[pair] =  makeTH2F(hist_name,31,-15.5,15.5,72,0.5,72.5);
      };

      adcSum[pair] -> Fill(hoDigi.ieta(),hoDigi.iphi(),hoDigi.sumADC);
      count[pair] -> Fill(hoDigi.ieta(),hoDigi.iphi());
    };
  };

  for (std::map<std::pair<int,int>,TH2F*>::iterator it=adcSum.begin(); it != adcSum.end(); ++it){
    it-> second -> Divide(count[it->first]);
  };

}
