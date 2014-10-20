#include <iostream>
#include "analysisClass.h"

int main(int argc, char* argv[]){

  const int Nparam=3;   // NUMBER OF PARAMETERS

  if(argc!=Nparam+1){
    std::cout << "main() : arcg = " << argc << " is different from " << Nparam+1 <<". Exiting." << std::endl;
    std::cout << "Usage  : ./main inputList.txt treeList.txt outputFile" << std::endl;
    exit (1);
  };
  
  std::string inputList(argv[1]);
  std::string treeList (argv[2]);
  std::string outFile  (argv[3]);
  
  analysisClass analysis (inputList, treeList, outFile);
  
  analysis.run();
}
