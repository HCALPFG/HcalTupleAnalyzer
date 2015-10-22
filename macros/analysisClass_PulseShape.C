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
  std::string eventListPath = "/afs/cern.ch/work/k/klo/hcal/L1Trigger/NTupleAnalyzer/output/ExpressPhysics_NoiseFilter_254833/ExpressPhysics254833_EventList.txt";
 
  //--------------------------------------------------------------------------------
  // Declare HCAL tree(s)
  //--------------------------------------------------------------------------------

  HcalTupleTree * tuple_tree = getTree<HcalTupleTree>("tuple_tree");
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
  std::vector<std::vector<int>> eventListMap;
  std::fstream file(eventListPath, std::ios_base::in);  
  std::string line;

  std::cout << "Loading EventList file" << std::endl;
  while ( std::getline(file, line)){
     std::istringstream iss(line);
     std::vector<std::string> entries;
     std::copy(std::istream_iterator<std::string>(iss),std::istream_iterator<std::string>(),std::back_inserter<std::vector<std::string> >(entries));
     int runNumber = std::stoi(entries[0]);
     int lumiSection = std::stoi(entries[1]);
     int eventNumber = std::stoi(entries[2]);
     eventListMap.push_back( std::vector<int> {runNumber,lumiSection,eventNumber} );
  };
  std::cout << "Finish loading EventList file" << std::endl;


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

    if ( (i + 1) % 10000 == 0 ) std::cout << "Processing event " << i + 1 << "/" << n_events << std::endl;

    if (std::find(eventListMap.begin(),eventListMap.end(),std::vector<int>{runNumber,lumiSection,eventNumber}) == eventListMap.end()) continue;
    
    sprintf(histName,"PulseShape_Central_%d_%d_%d",runNumber,lumiSection,eventNumber);
    sprintf(title," Central, %d %d %d ; TS ; FC",runNumber,lumiSection,eventNumber);
    TH1F * tempHist = makeTH1F(histName,10,-0.5,9.5);
    tempHist -> SetTitle(title);

    sprintf(histName,"PulseShape_EndCap_%d_%d_%d",runNumber,lumiSection,eventNumber);
    sprintf(title," EndCap, %d %d %d ; TS ; FC",runNumber,lumiSection,eventNumber);
    TH1F * tempHist3 = makeTH1F(histName,10,-0.5,9.5);
    tempHist3 -> SetTitle(title);

    sprintf(histName,"EtaPhi_%d_%d_%d",runNumber,lumiSection,eventNumber);
    sprintf(title," %d %d %d ; i#eta ; i#phi",runNumber,lumiSection,eventNumber);
    TH2F * tempHist2 = makeTH2F(histName,81,-40.5,40.5,72,0.5,72.5);
    tempHist2 -> SetTitle(title);
   

    //-----------------------------------------------------------------
    // Collections of HBHE
    //-----------------------------------------------------------------
    CollectionPtr hbheDigis (new Collection(*tuple_tree, tuple_tree -> HBHEDigiIEta -> size()));
    
    int nHBHEDigis = hbheDigis -> GetSize();
    int count = 0; int count3 = 0;
    for (int iHBHEDigi = 0; iHBHEDigi < nHBHEDigis; ++iHBHEDigi){
      HBHEDigi hbheDigi = hbheDigis -> GetConstituent<HBHEDigi>(iHBHEDigi);

      if ( hbheDigi.energy() < 5.0 ) continue; 
      for (int its = 0; its != 10; its++){
	if (abs(hbheDigi.ieta()) < 20){
	  count++;
          tempHist -> Fill ( its , hbheDigi.fc(its) );
	} else {
	  count3++;
	  tempHist3 -> Fill ( its, hbheDigi.fc(its) );
	};
        tempHist2 -> Fill ( hbheDigi.ieta() , hbheDigi.iphi() );
      };
      // int rawIndex = hbheDigi.getRawIndex();
      // std::cout << tuple_tree -> HBHEDigiFC -> at(rawIndex).size() << std::endl;
    };
    tempHist -> Scale( 1./count );
    tempHist3 -> Scale( 1./count3 );
    
  };
};
