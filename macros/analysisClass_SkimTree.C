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
  std::string outputFileName = "output/ExpressPhysics_254833_SkimTree.root";

  //--------------------------------------------------------------------------------
  // Open file
  //--------------------------------------------------------------------------------
  TFile * skimFile = new TFile(outputFileName.c_str(),"RECREATE");
 
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
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiSize", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiRecEnergy", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiIEta", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiIPhi", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HBHEDigiFC", kTRUE);

  //--------------------------------------------------------------------------------
  // Make trees
  //--------------------------------------------------------------------------------
  TTree * newTree = tuple_tree -> fChain -> GetTree() -> CloneTree(0);

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

    if (std::find(eventListMap.begin(),eventListMap.end(),std::vector<int>{runNumber,lumiSection,eventNumber}) == eventListMap.end()) continue;

    newTree -> Fill();
    
  };

  newTree->Write();
  skimFile -> Close();
};


