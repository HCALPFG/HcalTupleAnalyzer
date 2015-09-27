#include "baseClass.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

baseClass::~baseClass(){}
baseClass::baseClass( const std::string & fileList, 
		      const std::string & treeList,
		      const std::string & outFileName ):
  m_fileList     ( fileList ),
  m_treeList     ( treeList ),
  m_outFileName  ( outFileName ),
  m_badChannelList("data/bad_channel_list/bad_channels.txt")
{
  loadFileList();
  loadTreeList();
  loadBadChannelList();
  loadOutFile ();
}

void baseClass::loadBadChannelList(){
  std::ifstream infile(m_badChannelList.c_str());
  std::string line;
  while (std::getline(infile, line)) {
    std::istringstream iss(line);
    std::string subdet_string;
    int ieta, iphi, depth;
    if (!(iss >> ieta >> iphi >> depth >> subdet_string)) break;
    int subdet = -1;
    if      (subdet_string.compare("HB") == 0) subdet = 1;
    else if (subdet_string.compare("HE") == 0) subdet = 2;
    else if (subdet_string.compare("HO") == 0) subdet = 3;
    else if (subdet_string.compare("HF") == 0) subdet = 4;
    else subdet = -1;
    subdet = 0;
    m_badChannels.push_back(cell(subdet, ieta, iphi, depth));
  }
}

bool baseClass::isBadChannel(int subdet, int ieta, int iphi, int depth){
  cell hcal_cell (subdet, ieta, iphi, depth);
  bool is_bad = (std::find(m_badChannels.begin(), m_badChannels.end(), hcal_cell) != m_badChannels.end());
  return is_bad;
}

void baseClass::loadFileList(){
  std::ifstream infile(m_fileList.c_str());
  std::string line;
  while (std::getline(infile, line)) {
    std::istringstream iss(line);
    std::string file_name;
    std::string file_label;
    if (!(iss >> file_label >> file_name )){
      std::istringstream iss(line);
      file_label = std::string("no_label");
      if (!(iss >> file_name)) break;
      m_fileMap[file_label].push_back(file_name);
    }
    else {
      std::ifstream sub_file(file_name.c_str());
      std::string sub_line;
      while (std::getline(sub_file, sub_line)) {
	std::string sub_file_name;
	std::istringstream sub_iss(sub_line);
	if (!(sub_iss >> sub_file_name)) break;
	m_fileMap[file_label].push_back(sub_file_name);
      }
    }
    
  }
}

void baseClass::loadTreeList(){
  std::ifstream infile(m_treeList.c_str());
  std::string line;
  while (std::getline(infile, line)) {
    std::istringstream iss(line);
    std::string tree_name;
    std::string tree_path;
    if (!(iss >> tree_name >> tree_path)) break;
    if ( m_treeMap.find ( tree_name ) == m_treeMap.end() ){
      m_treeMap[tree_name] = tree_path;
    } else { 
      std::cout << "Error: Your tree list contains two identical keys." << std::endl;
      std::cout << "List is here:" << std::endl;
      std::cout << m_treeList << std::endl;
      std::cout << "Repeated key is this one: " << tree_name << std::endl;
      exit(0);
    }
  }
}

void baseClass::loadOutFile(){
  m_outFile = new TFile (m_outFileName.c_str(), "RECREATE");
}

TChain* baseClass::getChain(std::string tree_name, std::string file_label ){
  TChain * chain = new TChain(tree_name.c_str());
  std::vector<std::string> file_names = m_fileMap[file_label];
  std::vector<std::string>::iterator i_file_name   = file_names.begin();
  std::vector<std::string>::iterator end_file_name = file_names.end();
  for (; i_file_name != end_file_name; ++i_file_name){
    chain -> Add (i_file_name->c_str());
  }
  return chain;
}

TH1F* baseClass::makeTH1F(const char * name, int nbins, float xmin, float xmax ){
  TH1F* hist = new TH1F(name, name, nbins, xmin, xmax );
  m_objects.push_back(hist);
  return hist;
}

TH2F* baseClass::makeTH2F(const char * name, int nbinsx, float xmin, float xmax, int nbinsy, float ymin, float ymax){
  TH2F* hist = new TH2F(name, name, nbinsx, xmin, xmax, nbinsy, ymin, ymax );
  m_objects.push_back(hist);
  return hist;
}

TGraph* baseClass::makeTGraph(int n, const double* x, const double* y){
  TGraph* graph = new TGraph(n,x,y);
  m_objects.push_back(graph);
  return graph;
};

TGraph* baseClass::makeTGraph(){
  TGraph* graph = new TGraph();
  m_objects.push_back(graph);
  return graph;
};

void baseClass::write(){
  m_outFile -> cd();
  std::vector<TObject*>::iterator i_object   = m_objects.begin();
  std::vector<TObject*>::iterator end_object = m_objects.end  ();
  for (; i_object != end_object; ++i_object)
    (*i_object) -> Write();
}

void baseClass::print(){
  std::cout << "-----------------------------------------------------------------------------" << std::endl;

  std::cout << "Analyzing these files (" << m_fileList << "):" << std::endl;
  std::map<std::string,std::vector<std::string> >::iterator i_file_label   = m_fileMap.begin();
  std::map<std::string,std::vector<std::string> >::iterator end_file_label = m_fileMap.end();
  for (; i_file_label != end_file_label; ++i_file_label){
    std::cout << "\t" << i_file_label -> first << std::endl;
    std::vector<std::string>::iterator i_file   = i_file_label -> second.begin();
    std::vector<std::string>::iterator end_file = i_file_label -> second.end();
    for (; i_file != end_file; ++i_file){
      std::cout << "\t\t" << *i_file << std::endl;
    }
  }
  std::cout << std::endl;
  std::cout << "Using these trees (" << m_treeList << "):" << std::endl;
  std::map<std::string,std::string>::iterator i_tree   = m_treeMap.begin();
  std::map<std::string,std::string>::iterator end_tree = m_treeMap.end();
  for (; i_tree != end_tree; ++i_tree){
    std::cout << "\t" << i_tree -> first << std::endl;
    std::cout << "\t\t" << i_tree -> second << std::endl;
  }
  std::cout << std::endl;
  std::cout << "Writing output here:" << std::endl;
  std::cout << "\t" << m_outFileName << std::endl;
  std::cout << "-----------------------------------------------------------------------------" << std::endl;

}

void baseClass::run(){
  print();
  loop ();
  write();
}

void baseClass::getTriggers(std::string * HLTKey ,  
                            std::vector<std::string> * names, 
                            std::vector<bool>        * decisions,
                            std::vector<int>         * prescales ){
  triggerDecisionMap_.clear();
  triggerPrescaleMap_.clear();

  int ntriggers = names -> size();

  for (int i = 0; i < ntriggers; ++i){
    triggerDecisionMap_[ (*names)[i].c_str() ] = (*decisions)[i];
    triggerPrescaleMap_[ (*names)[i].c_str() ] = (*prescales)[i];
  }
}

void baseClass::printTriggers(){
  std::map<std::string, int>::iterator i     = triggerPrescaleMap_.begin();
  std::map<std::string, int>::iterator i_end = triggerPrescaleMap_.end();
  std::cout << "Triggers include:" << std::endl;
  for (; i != i_end; ++i) std::cout << "\t" << i -> second << "\t\"" << i -> first << "\"" << std::endl;
}

bool baseClass::triggerFired ( const char* name ) {
  std::map<std::string, bool>::iterator i = triggerDecisionMap_.find ( name ) ;
  if ( i == triggerDecisionMap_.end()) return false;
  else return i -> second;
}

int baseClass::triggerPrescale ( const char* name ) { 
  std::map<std::string, int>::iterator i = triggerPrescaleMap_.find ( name ) ;
  if ( i == triggerPrescaleMap_.end()) return -999;
  else return i -> second;
}
