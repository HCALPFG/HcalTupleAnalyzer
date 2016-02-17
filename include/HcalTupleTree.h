//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Jan 22 14:11:47 2016 by ROOT version 5.34/32
// from TTree tree/
// found on file: test_uTCA.root // Root output of analysis_uHBHECommissioning_cfg.py
//////////////////////////////////////////////////////////

#ifndef HcalTupleTree_h
#define HcalTupleTree_h
using namespace std;

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"
#include "vector"

// Fixed size dimensions of array or collections stored in the TTree if any.

class HcalTupleTree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   vector<float>   *HBHEDigiEta;
   vector<float>   *HBHEDigiPhi;
   vector<float>   *HBHEDigiRecEnergy;
   vector<float>   *HBHEDigiRecTime;
   vector<float>   *HFDigiEta;
   vector<float>   *HFDigiPhi;
   vector<float>   *HFDigiRecEnergy;
   vector<float>   *HFDigiRecTime;
   vector<float>   *HODigiEta;
   vector<float>   *HODigiPhi;
   vector<float>   *HODigiRecEnergy;
   vector<float>   *HODigiRecTime;
   vector<vector<float> > *HBHEDigiAllFC;
   vector<vector<float> > *HBHEDigiEnergy;
   vector<vector<float> > *HBHEDigiFC;
   vector<vector<float> > *HBHEDigiGain;
   vector<vector<float> > *HBHEDigiNomFC;
   vector<vector<float> > *HBHEDigiPedFC;
   vector<vector<float> > *HBHEDigiRCGain;
   vector<vector<float> > *HFDigiAllFC;
   vector<vector<float> > *HFDigiEnergy;
   vector<vector<float> > *HFDigiFC;
   vector<vector<float> > *HFDigiGain;
   vector<vector<float> > *HFDigiNomFC;
   vector<vector<float> > *HFDigiPedFC;
   vector<vector<float> > *HFDigiRCGain;
   vector<vector<float> > *HODigiAllFC;
   vector<vector<float> > *HODigiEnergy;
   vector<vector<float> > *HODigiFC;
   vector<vector<float> > *HODigiGain;
   vector<vector<float> > *HODigiNomFC;
   vector<vector<float> > *HODigiPedFC;
   vector<vector<float> > *HODigiRCGain;
   vector<int>     *HBHEDigiDepth;
   vector<int>     *HBHEDigiElectronicsID;
   vector<int>     *HBHEDigiFiberIdleOffset;
   vector<int>     *HBHEDigiIEta;
   vector<int>     *HBHEDigiIPhi;
   vector<int>     *HBHEDigiPresamples;
   vector<int>     *HBHEDigiRawID;
   vector<int>     *HBHEDigiSize;
   vector<int>     *HBHEDigiSubdet;
   vector<int>     *HFDigiDepth;
   vector<int>     *HFDigiElectronicsID;
   vector<int>     *HFDigiFiberIdleOffset;
   vector<int>     *HFDigiIEta;
   vector<int>     *HFDigiIPhi;
   vector<int>     *HFDigiPresamples;
   vector<int>     *HFDigiRawID;
   vector<int>     *HFDigiSize;
   vector<int>     *HFDigiSubdet;
   vector<int>     *HODigiDepth;
   vector<int>     *HODigiElectronicsID;
   vector<int>     *HODigiFiberIdleOffset;
   vector<int>     *HODigiIEta;
   vector<int>     *HODigiIPhi;
   vector<int>     *HODigiPresamples;
   vector<int>     *HODigiRawID;
   vector<int>     *HODigiSize;
   vector<int>     *HODigiSubdet;
   vector<int>     *HcalTriggerPrimitiveCompressedEtSOI;
   vector<int>     *HcalTriggerPrimitiveFineGrainSOI;
   vector<int>     *HcalTriggerPrimitiveIEta;
   vector<int>     *HcalTriggerPrimitiveIPhi;
   vector<int>     *HcalTriggerPrimitivePresamples;
   vector<int>     *HcalTriggerPrimitiveSize;
   vector<int>     *HcalUnpackerBadDigiDepth;
   vector<int>     *HcalUnpackerBadDigiIEta;
   vector<int>     *HcalUnpackerBadDigiIPhi;
   vector<int>     *HcalUnpackerBadDigiSubdet;
   vector<vector<int> > *HBHEDigiADC;
   vector<vector<int> > *HBHEDigiCapID;
   vector<vector<int> > *HBHEDigiDV;
   vector<vector<int> > *HBHEDigiER;
   vector<vector<int> > *HBHEDigiFiber;
   vector<vector<int> > *HBHEDigiFiberChan;
   vector<vector<int> > *HBHEDigiLADC;
   vector<vector<int> > *HBHEDigiRaw;
   vector<vector<int> > *HFDigiADC;
   vector<vector<int> > *HFDigiCapID;
   vector<vector<int> > *HFDigiDV;
   vector<vector<int> > *HFDigiER;
   vector<vector<int> > *HFDigiFiber;
   vector<vector<int> > *HFDigiFiberChan;
   vector<vector<int> > *HFDigiLADC;
   vector<vector<int> > *HFDigiRaw;
   vector<vector<int> > *HODigiADC;
   vector<vector<int> > *HODigiCapID;
   vector<vector<int> > *HODigiDV;
   vector<vector<int> > *HODigiER;
   vector<vector<int> > *HODigiFiber;
   vector<vector<int> > *HODigiFiberChan;
   vector<vector<int> > *HODigiLADC;
   vector<vector<int> > *HODigiRaw;
   vector<vector<int> > *HcalTriggerPrimitiveCompressedEt;
   vector<vector<int> > *HcalTriggerPrimitiveFineGrain;
   vector<vector<int> > *HcalTriggerPrimitiveHBHEDigiIndex;
   vector<vector<int> > *HcalTriggerPrimitiveHFDigiIndex;
   UInt_t          bx;
   UInt_t          event;
   UInt_t          ls;
   UInt_t          run;
   UInt_t          HcalUnpackerAnyValid;
   UInt_t          HcalUnpackerBSYSpigots;
   UInt_t          HcalUnpackerBadQualityDigis;
   UInt_t          HcalUnpackerEmptySpigots;
   UInt_t          HcalUnpackerErrorFree;
   UInt_t          HcalUnpackerHasCalib;
   UInt_t          HcalUnpackerNZS;
   UInt_t          HcalUnpackerOFWSpigots;
   UInt_t          HcalUnpackerSpigotFormatErrors;
   UInt_t          HcalUnpackerTotalDigis;
   UInt_t          HcalUnpackerTotalHOTPDigis;
   UInt_t          HcalUnpackerTotalTPDigis;

   // List of branches
   TBranch        *b_HBHEDigiEta;   //!
   TBranch        *b_HBHEDigiPhi;   //!
   TBranch        *b_HBHEDigiRecEnergy;   //!
   TBranch        *b_HBHEDigiRecTime;   //!
   TBranch        *b_HFDigiEta;   //!
   TBranch        *b_HFDigiPhi;   //!
   TBranch        *b_HFDigiRecEnergy;   //!
   TBranch        *b_HFDigiRecTime;   //!
   TBranch        *b_HODigiEta;   //!
   TBranch        *b_HODigiPhi;   //!
   TBranch        *b_HODigiRecEnergy;   //!
   TBranch        *b_HODigiRecTime;   //!
   TBranch        *b_HBHEDigiAllFC;   //!
   TBranch        *b_HBHEDigiEnergy;   //!
   TBranch        *b_HBHEDigiFC;   //!
   TBranch        *b_HBHEDigiGain;   //!
   TBranch        *b_HBHEDigiNomFC;   //!
   TBranch        *b_HBHEDigiPedFC;   //!
   TBranch        *b_HBHEDigiRCGain;   //!
   TBranch        *b_HFDigiAllFC;   //!
   TBranch        *b_HFDigiEnergy;   //!
   TBranch        *b_HFDigiFC;   //!
   TBranch        *b_HFDigiGain;   //!
   TBranch        *b_HFDigiNomFC;   //!
   TBranch        *b_HFDigiPedFC;   //!
   TBranch        *b_HFDigiRCGain;   //!
   TBranch        *b_HODigiAllFC;   //!
   TBranch        *b_HODigiEnergy;   //!
   TBranch        *b_HODigiFC;   //!
   TBranch        *b_HODigiGain;   //!
   TBranch        *b_HODigiNomFC;   //!
   TBranch        *b_HODigiPedFC;   //!
   TBranch        *b_HODigiRCGain;   //!
   TBranch        *b_HBHEDigiDepth;   //!
   TBranch        *b_HBHEDigiElectronicsID;   //!
   TBranch        *b_HBHEDigiFiberIdleOffset;   //!
   TBranch        *b_HBHEDigiIEta;   //!
   TBranch        *b_HBHEDigiIPhi;   //!
   TBranch        *b_HBHEDigiPresamples;   //!
   TBranch        *b_HBHEDigiRawID;   //!
   TBranch        *b_HBHEDigiSize;   //!
   TBranch        *b_HBHEDigiSubdet;   //!
   TBranch        *b_HFDigiDepth;   //!
   TBranch        *b_HFDigiElectronicsID;   //!
   TBranch        *b_HFDigiFiberIdleOffset;   //!
   TBranch        *b_HFDigiIEta;   //!
   TBranch        *b_HFDigiIPhi;   //!
   TBranch        *b_HFDigiPresamples;   //!
   TBranch        *b_HFDigiRawID;   //!
   TBranch        *b_HFDigiSize;   //!
   TBranch        *b_HFDigiSubdet;   //!
   TBranch        *b_HODigiDepth;   //!
   TBranch        *b_HODigiElectronicsID;   //!
   TBranch        *b_HODigiFiberIdleOffset;   //!
   TBranch        *b_HODigiIEta;   //!
   TBranch        *b_HODigiIPhi;   //!
   TBranch        *b_HODigiPresamples;   //!
   TBranch        *b_HODigiRawID;   //!
   TBranch        *b_HODigiSize;   //!
   TBranch        *b_HODigiSubdet;   //!
   TBranch        *b_HcalTriggerPrimitiveCompressedEtSOI;   //!
   TBranch        *b_HcalTriggerPrimitiveFineGrainSOI;   //!
   TBranch        *b_HcalTriggerPrimitiveIEta;   //!
   TBranch        *b_HcalTriggerPrimitiveIPhi;   //!
   TBranch        *b_HcalTriggerPrimitivePresamples;   //!
   TBranch        *b_HcalTriggerPrimitiveSize;   //!
   TBranch        *b_HcalUnpackerBadDigiDepth;   //!
   TBranch        *b_HcalUnpackerBadDigiIEta;   //!
   TBranch        *b_HcalUnpackerBadDigiIPhi;   //!
   TBranch        *b_HcalUnpackerBadDigiSubdet;   //!
   TBranch        *b_HBHEDigiADC;   //!
   TBranch        *b_HBHEDigiCapID;   //!
   TBranch        *b_HBHEDigiDV;   //!
   TBranch        *b_HBHEDigiER;   //!
   TBranch        *b_HBHEDigiFiber;   //!
   TBranch        *b_HBHEDigiFiberChan;   //!
   TBranch        *b_HBHEDigiLADC;   //!
   TBranch        *b_HBHEDigiRaw;   //!
   TBranch        *b_HFDigiADC;   //!
   TBranch        *b_HFDigiCapID;   //!
   TBranch        *b_HFDigiDV;   //!
   TBranch        *b_HFDigiER;   //!
   TBranch        *b_HFDigiFiber;   //!
   TBranch        *b_HFDigiFiberChan;   //!
   TBranch        *b_HFDigiLADC;   //!
   TBranch        *b_HFDigiRaw;   //!
   TBranch        *b_HODigiADC;   //!
   TBranch        *b_HODigiCapID;   //!
   TBranch        *b_HODigiDV;   //!
   TBranch        *b_HODigiER;   //!
   TBranch        *b_HODigiFiber;   //!
   TBranch        *b_HODigiFiberChan;   //!
   TBranch        *b_HODigiLADC;   //!
   TBranch        *b_HODigiRaw;   //!
   TBranch        *b_HcalTriggerPrimitiveCompressedEt;   //!
   TBranch        *b_HcalTriggerPrimitiveFineGrain;   //!
   TBranch        *b_HcalTriggerPrimitiveHBHEDigiIndex;   //!
   TBranch        *b_HcalTriggerPrimitiveHFDigiIndex;   //!
   TBranch        *b_bx;   //!
   TBranch        *b_event;   //!
   TBranch        *b_ls;   //!
   TBranch        *b_run;   //!
   TBranch        *b_HcalUnpackerAnyValid;   //!
   TBranch        *b_HcalUnpackerBSYSpigots;   //!
   TBranch        *b_HcalUnpackerBadQualityDigis;   //!
   TBranch        *b_HcalUnpackerEmptySpigots;   //!
   TBranch        *b_HcalUnpackerErrorFree;   //!
   TBranch        *b_HcalUnpackerHasCalib;   //!
   TBranch        *b_HcalUnpackerNZS;   //!
   TBranch        *b_HcalUnpackerOFWSpigots;   //!
   TBranch        *b_HcalUnpackerSpigotFormatErrors;   //!
   TBranch        *b_HcalUnpackerTotalDigis;   //!
   TBranch        *b_HcalUnpackerTotalHOTPDigis;   //!
   TBranch        *b_HcalUnpackerTotalTPDigis;   //!

   HcalTupleTree(TTree *tree=0);
   virtual ~HcalTupleTree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef HcalTupleTree_cxx
HcalTupleTree::HcalTupleTree(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("test_uTCA.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("test_uTCA.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("test_uTCA.root:/HcalTupleTree");
      dir->GetObject("tree",tree);

   }
   Init(tree);
}

HcalTupleTree::~HcalTupleTree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t HcalTupleTree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t HcalTupleTree::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void HcalTupleTree::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   HBHEDigiEta = 0;
   HBHEDigiPhi = 0;
   HBHEDigiRecEnergy = 0;
   HBHEDigiRecTime = 0;
   HFDigiEta = 0;
   HFDigiPhi = 0;
   HFDigiRecEnergy = 0;
   HFDigiRecTime = 0;
   HODigiEta = 0;
   HODigiPhi = 0;
   HODigiRecEnergy = 0;
   HODigiRecTime = 0;
   HBHEDigiAllFC = 0;
   HBHEDigiEnergy = 0;
   HBHEDigiFC = 0;
   HBHEDigiGain = 0;
   HBHEDigiNomFC = 0;
   HBHEDigiPedFC = 0;
   HBHEDigiRCGain = 0;
   HFDigiAllFC = 0;
   HFDigiEnergy = 0;
   HFDigiFC = 0;
   HFDigiGain = 0;
   HFDigiNomFC = 0;
   HFDigiPedFC = 0;
   HFDigiRCGain = 0;
   HODigiAllFC = 0;
   HODigiEnergy = 0;
   HODigiFC = 0;
   HODigiGain = 0;
   HODigiNomFC = 0;
   HODigiPedFC = 0;
   HODigiRCGain = 0;
   HBHEDigiDepth = 0;
   HBHEDigiElectronicsID = 0;
   HBHEDigiFiberIdleOffset = 0;
   HBHEDigiIEta = 0;
   HBHEDigiIPhi = 0;
   HBHEDigiPresamples = 0;
   HBHEDigiRawID = 0;
   HBHEDigiSize = 0;
   HBHEDigiSubdet = 0;
   HFDigiDepth = 0;
   HFDigiElectronicsID = 0;
   HFDigiFiberIdleOffset = 0;
   HFDigiIEta = 0;
   HFDigiIPhi = 0;
   HFDigiPresamples = 0;
   HFDigiRawID = 0;
   HFDigiSize = 0;
   HFDigiSubdet = 0;
   HODigiDepth = 0;
   HODigiElectronicsID = 0;
   HODigiFiberIdleOffset = 0;
   HODigiIEta = 0;
   HODigiIPhi = 0;
   HODigiPresamples = 0;
   HODigiRawID = 0;
   HODigiSize = 0;
   HODigiSubdet = 0;
   HcalTriggerPrimitiveCompressedEtSOI = 0;
   HcalTriggerPrimitiveFineGrainSOI = 0;
   HcalTriggerPrimitiveIEta = 0;
   HcalTriggerPrimitiveIPhi = 0;
   HcalTriggerPrimitivePresamples = 0;
   HcalTriggerPrimitiveSize = 0;
   HcalUnpackerBadDigiDepth = 0;
   HcalUnpackerBadDigiIEta = 0;
   HcalUnpackerBadDigiIPhi = 0;
   HcalUnpackerBadDigiSubdet = 0;
   HBHEDigiADC = 0;
   HBHEDigiCapID = 0;
   HBHEDigiDV = 0;
   HBHEDigiER = 0;
   HBHEDigiFiber = 0;
   HBHEDigiFiberChan = 0;
   HBHEDigiLADC = 0;
   HBHEDigiRaw = 0;
   HFDigiADC = 0;
   HFDigiCapID = 0;
   HFDigiDV = 0;
   HFDigiER = 0;
   HFDigiFiber = 0;
   HFDigiFiberChan = 0;
   HFDigiLADC = 0;
   HFDigiRaw = 0;
   HODigiADC = 0;
   HODigiCapID = 0;
   HODigiDV = 0;
   HODigiER = 0;
   HODigiFiber = 0;
   HODigiFiberChan = 0;
   HODigiLADC = 0;
   HODigiRaw = 0;
   HcalTriggerPrimitiveCompressedEt = 0;
   HcalTriggerPrimitiveFineGrain = 0;
   HcalTriggerPrimitiveHBHEDigiIndex = 0;
   HcalTriggerPrimitiveHFDigiIndex = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("HBHEDigiEta", &HBHEDigiEta, &b_HBHEDigiEta);
   fChain->SetBranchAddress("HBHEDigiPhi", &HBHEDigiPhi, &b_HBHEDigiPhi);
   fChain->SetBranchAddress("HBHEDigiRecEnergy", &HBHEDigiRecEnergy, &b_HBHEDigiRecEnergy);
   fChain->SetBranchAddress("HBHEDigiRecTime", &HBHEDigiRecTime, &b_HBHEDigiRecTime);
   fChain->SetBranchAddress("HFDigiEta", &HFDigiEta, &b_HFDigiEta);
   fChain->SetBranchAddress("HFDigiPhi", &HFDigiPhi, &b_HFDigiPhi);
   fChain->SetBranchAddress("HFDigiRecEnergy", &HFDigiRecEnergy, &b_HFDigiRecEnergy);
   fChain->SetBranchAddress("HFDigiRecTime", &HFDigiRecTime, &b_HFDigiRecTime);
   fChain->SetBranchAddress("HODigiEta", &HODigiEta, &b_HODigiEta);
   fChain->SetBranchAddress("HODigiPhi", &HODigiPhi, &b_HODigiPhi);
   fChain->SetBranchAddress("HODigiRecEnergy", &HODigiRecEnergy, &b_HODigiRecEnergy);
   fChain->SetBranchAddress("HODigiRecTime", &HODigiRecTime, &b_HODigiRecTime);
   fChain->SetBranchAddress("HBHEDigiAllFC", &HBHEDigiAllFC, &b_HBHEDigiAllFC);
   fChain->SetBranchAddress("HBHEDigiEnergy", &HBHEDigiEnergy, &b_HBHEDigiEnergy);
   fChain->SetBranchAddress("HBHEDigiFC", &HBHEDigiFC, &b_HBHEDigiFC);
   fChain->SetBranchAddress("HBHEDigiGain", &HBHEDigiGain, &b_HBHEDigiGain);
   fChain->SetBranchAddress("HBHEDigiNomFC", &HBHEDigiNomFC, &b_HBHEDigiNomFC);
   fChain->SetBranchAddress("HBHEDigiPedFC", &HBHEDigiPedFC, &b_HBHEDigiPedFC);
   fChain->SetBranchAddress("HBHEDigiRCGain", &HBHEDigiRCGain, &b_HBHEDigiRCGain);
   fChain->SetBranchAddress("HFDigiAllFC", &HFDigiAllFC, &b_HFDigiAllFC);
   fChain->SetBranchAddress("HFDigiEnergy", &HFDigiEnergy, &b_HFDigiEnergy);
   fChain->SetBranchAddress("HFDigiFC", &HFDigiFC, &b_HFDigiFC);
   fChain->SetBranchAddress("HFDigiGain", &HFDigiGain, &b_HFDigiGain);
   fChain->SetBranchAddress("HFDigiNomFC", &HFDigiNomFC, &b_HFDigiNomFC);
   fChain->SetBranchAddress("HFDigiPedFC", &HFDigiPedFC, &b_HFDigiPedFC);
   fChain->SetBranchAddress("HFDigiRCGain", &HFDigiRCGain, &b_HFDigiRCGain);
   fChain->SetBranchAddress("HODigiAllFC", &HODigiAllFC, &b_HODigiAllFC);
   fChain->SetBranchAddress("HODigiEnergy", &HODigiEnergy, &b_HODigiEnergy);
   fChain->SetBranchAddress("HODigiFC", &HODigiFC, &b_HODigiFC);
   fChain->SetBranchAddress("HODigiGain", &HODigiGain, &b_HODigiGain);
   fChain->SetBranchAddress("HODigiNomFC", &HODigiNomFC, &b_HODigiNomFC);
   fChain->SetBranchAddress("HODigiPedFC", &HODigiPedFC, &b_HODigiPedFC);
   fChain->SetBranchAddress("HODigiRCGain", &HODigiRCGain, &b_HODigiRCGain);
   fChain->SetBranchAddress("HBHEDigiDepth", &HBHEDigiDepth, &b_HBHEDigiDepth);
   fChain->SetBranchAddress("HBHEDigiElectronicsID", &HBHEDigiElectronicsID, &b_HBHEDigiElectronicsID);
   fChain->SetBranchAddress("HBHEDigiFiberIdleOffset", &HBHEDigiFiberIdleOffset, &b_HBHEDigiFiberIdleOffset);
   fChain->SetBranchAddress("HBHEDigiIEta", &HBHEDigiIEta, &b_HBHEDigiIEta);
   fChain->SetBranchAddress("HBHEDigiIPhi", &HBHEDigiIPhi, &b_HBHEDigiIPhi);
   fChain->SetBranchAddress("HBHEDigiPresamples", &HBHEDigiPresamples, &b_HBHEDigiPresamples);
   fChain->SetBranchAddress("HBHEDigiRawID", &HBHEDigiRawID, &b_HBHEDigiRawID);
   fChain->SetBranchAddress("HBHEDigiSize", &HBHEDigiSize, &b_HBHEDigiSize);
   fChain->SetBranchAddress("HBHEDigiSubdet", &HBHEDigiSubdet, &b_HBHEDigiSubdet);
   fChain->SetBranchAddress("HFDigiDepth", &HFDigiDepth, &b_HFDigiDepth);
   fChain->SetBranchAddress("HFDigiElectronicsID", &HFDigiElectronicsID, &b_HFDigiElectronicsID);
   fChain->SetBranchAddress("HFDigiFiberIdleOffset", &HFDigiFiberIdleOffset, &b_HFDigiFiberIdleOffset);
   fChain->SetBranchAddress("HFDigiIEta", &HFDigiIEta, &b_HFDigiIEta);
   fChain->SetBranchAddress("HFDigiIPhi", &HFDigiIPhi, &b_HFDigiIPhi);
   fChain->SetBranchAddress("HFDigiPresamples", &HFDigiPresamples, &b_HFDigiPresamples);
   fChain->SetBranchAddress("HFDigiRawID", &HFDigiRawID, &b_HFDigiRawID);
   fChain->SetBranchAddress("HFDigiSize", &HFDigiSize, &b_HFDigiSize);
   fChain->SetBranchAddress("HFDigiSubdet", &HFDigiSubdet, &b_HFDigiSubdet);
   fChain->SetBranchAddress("HODigiDepth", &HODigiDepth, &b_HODigiDepth);
   fChain->SetBranchAddress("HODigiElectronicsID", &HODigiElectronicsID, &b_HODigiElectronicsID);
   fChain->SetBranchAddress("HODigiFiberIdleOffset", &HODigiFiberIdleOffset, &b_HODigiFiberIdleOffset);
   fChain->SetBranchAddress("HODigiIEta", &HODigiIEta, &b_HODigiIEta);
   fChain->SetBranchAddress("HODigiIPhi", &HODigiIPhi, &b_HODigiIPhi);
   fChain->SetBranchAddress("HODigiPresamples", &HODigiPresamples, &b_HODigiPresamples);
   fChain->SetBranchAddress("HODigiRawID", &HODigiRawID, &b_HODigiRawID);
   fChain->SetBranchAddress("HODigiSize", &HODigiSize, &b_HODigiSize);
   fChain->SetBranchAddress("HODigiSubdet", &HODigiSubdet, &b_HODigiSubdet);
   fChain->SetBranchAddress("HcalTriggerPrimitiveCompressedEtSOI", &HcalTriggerPrimitiveCompressedEtSOI, &b_HcalTriggerPrimitiveCompressedEtSOI);
   fChain->SetBranchAddress("HcalTriggerPrimitiveFineGrainSOI", &HcalTriggerPrimitiveFineGrainSOI, &b_HcalTriggerPrimitiveFineGrainSOI);
   fChain->SetBranchAddress("HcalTriggerPrimitiveIEta", &HcalTriggerPrimitiveIEta, &b_HcalTriggerPrimitiveIEta);
   fChain->SetBranchAddress("HcalTriggerPrimitiveIPhi", &HcalTriggerPrimitiveIPhi, &b_HcalTriggerPrimitiveIPhi);
   fChain->SetBranchAddress("HcalTriggerPrimitivePresamples", &HcalTriggerPrimitivePresamples, &b_HcalTriggerPrimitivePresamples);
   fChain->SetBranchAddress("HcalTriggerPrimitiveSize", &HcalTriggerPrimitiveSize, &b_HcalTriggerPrimitiveSize);
   fChain->SetBranchAddress("HcalUnpackerBadDigiDepth", &HcalUnpackerBadDigiDepth, &b_HcalUnpackerBadDigiDepth);
   fChain->SetBranchAddress("HcalUnpackerBadDigiIEta", &HcalUnpackerBadDigiIEta, &b_HcalUnpackerBadDigiIEta);
   fChain->SetBranchAddress("HcalUnpackerBadDigiIPhi", &HcalUnpackerBadDigiIPhi, &b_HcalUnpackerBadDigiIPhi);
   fChain->SetBranchAddress("HcalUnpackerBadDigiSubdet", &HcalUnpackerBadDigiSubdet, &b_HcalUnpackerBadDigiSubdet);
   fChain->SetBranchAddress("HBHEDigiADC", &HBHEDigiADC, &b_HBHEDigiADC);
   fChain->SetBranchAddress("HBHEDigiCapID", &HBHEDigiCapID, &b_HBHEDigiCapID);
   fChain->SetBranchAddress("HBHEDigiDV", &HBHEDigiDV, &b_HBHEDigiDV);
   fChain->SetBranchAddress("HBHEDigiER", &HBHEDigiER, &b_HBHEDigiER);
   fChain->SetBranchAddress("HBHEDigiFiber", &HBHEDigiFiber, &b_HBHEDigiFiber);
   fChain->SetBranchAddress("HBHEDigiFiberChan", &HBHEDigiFiberChan, &b_HBHEDigiFiberChan);
   fChain->SetBranchAddress("HBHEDigiLADC", &HBHEDigiLADC, &b_HBHEDigiLADC);
   fChain->SetBranchAddress("HBHEDigiRaw", &HBHEDigiRaw, &b_HBHEDigiRaw);
   fChain->SetBranchAddress("HFDigiADC", &HFDigiADC, &b_HFDigiADC);
   fChain->SetBranchAddress("HFDigiCapID", &HFDigiCapID, &b_HFDigiCapID);
   fChain->SetBranchAddress("HFDigiDV", &HFDigiDV, &b_HFDigiDV);
   fChain->SetBranchAddress("HFDigiER", &HFDigiER, &b_HFDigiER);
   fChain->SetBranchAddress("HFDigiFiber", &HFDigiFiber, &b_HFDigiFiber);
   fChain->SetBranchAddress("HFDigiFiberChan", &HFDigiFiberChan, &b_HFDigiFiberChan);
   fChain->SetBranchAddress("HFDigiLADC", &HFDigiLADC, &b_HFDigiLADC);
   fChain->SetBranchAddress("HFDigiRaw", &HFDigiRaw, &b_HFDigiRaw);
   fChain->SetBranchAddress("HODigiADC", &HODigiADC, &b_HODigiADC);
   fChain->SetBranchAddress("HODigiCapID", &HODigiCapID, &b_HODigiCapID);
   fChain->SetBranchAddress("HODigiDV", &HODigiDV, &b_HODigiDV);
   fChain->SetBranchAddress("HODigiER", &HODigiER, &b_HODigiER);
   fChain->SetBranchAddress("HODigiFiber", &HODigiFiber, &b_HODigiFiber);
   fChain->SetBranchAddress("HODigiFiberChan", &HODigiFiberChan, &b_HODigiFiberChan);
   fChain->SetBranchAddress("HODigiLADC", &HODigiLADC, &b_HODigiLADC);
   fChain->SetBranchAddress("HODigiRaw", &HODigiRaw, &b_HODigiRaw);
   fChain->SetBranchAddress("HcalTriggerPrimitiveCompressedEt", &HcalTriggerPrimitiveCompressedEt, &b_HcalTriggerPrimitiveCompressedEt);
   fChain->SetBranchAddress("HcalTriggerPrimitiveFineGrain", &HcalTriggerPrimitiveFineGrain, &b_HcalTriggerPrimitiveFineGrain);
   fChain->SetBranchAddress("HcalTriggerPrimitiveHBHEDigiIndex", &HcalTriggerPrimitiveHBHEDigiIndex, &b_HcalTriggerPrimitiveHBHEDigiIndex);
   fChain->SetBranchAddress("HcalTriggerPrimitiveHFDigiIndex", &HcalTriggerPrimitiveHFDigiIndex, &b_HcalTriggerPrimitiveHFDigiIndex);
   fChain->SetBranchAddress("bx", &bx, &b_bx);
   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("ls", &ls, &b_ls);
   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("HcalUnpackerAnyValid", &HcalUnpackerAnyValid, &b_HcalUnpackerAnyValid);
   fChain->SetBranchAddress("HcalUnpackerBSYSpigots", &HcalUnpackerBSYSpigots, &b_HcalUnpackerBSYSpigots);
   fChain->SetBranchAddress("HcalUnpackerBadQualityDigis", &HcalUnpackerBadQualityDigis, &b_HcalUnpackerBadQualityDigis);
   fChain->SetBranchAddress("HcalUnpackerEmptySpigots", &HcalUnpackerEmptySpigots, &b_HcalUnpackerEmptySpigots);
   fChain->SetBranchAddress("HcalUnpackerErrorFree", &HcalUnpackerErrorFree, &b_HcalUnpackerErrorFree);
   fChain->SetBranchAddress("HcalUnpackerHasCalib", &HcalUnpackerHasCalib, &b_HcalUnpackerHasCalib);
   fChain->SetBranchAddress("HcalUnpackerNZS", &HcalUnpackerNZS, &b_HcalUnpackerNZS);
   fChain->SetBranchAddress("HcalUnpackerOFWSpigots", &HcalUnpackerOFWSpigots, &b_HcalUnpackerOFWSpigots);
   fChain->SetBranchAddress("HcalUnpackerSpigotFormatErrors", &HcalUnpackerSpigotFormatErrors, &b_HcalUnpackerSpigotFormatErrors);
   fChain->SetBranchAddress("HcalUnpackerTotalDigis", &HcalUnpackerTotalDigis, &b_HcalUnpackerTotalDigis);
   fChain->SetBranchAddress("HcalUnpackerTotalHOTPDigis", &HcalUnpackerTotalHOTPDigis, &b_HcalUnpackerTotalHOTPDigis);
   fChain->SetBranchAddress("HcalUnpackerTotalTPDigis", &HcalUnpackerTotalTPDigis, &b_HcalUnpackerTotalTPDigis);
   Notify();
}

Bool_t HcalTupleTree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void HcalTupleTree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t HcalTupleTree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef HcalTupleTree_cxx
