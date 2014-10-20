//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Oct 20 06:26:05 2014 by ROOT version 5.34/18
// from TTree tree/
// found on file: root://eoscms//eos/cms/store/user/eberry/HCALPFG/MWGR8_227391_HcalHPDNoise_v3/MWGR8_227391_HcalHPDNoise_0.root
//////////////////////////////////////////////////////////

#ifndef HcalTupleTree_h
#define HcalTupleTree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <string>
#include <vector>
#include <vector>
#include <vector>
#include <vector>
#include <vector>

using namespace std;

// Fixed size dimensions of array or collections stored in the TTree if any.

class HcalTupleTree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   string          *HLTKey;
   vector<string>  *HLTInsideDatasetTriggerNames;
   vector<string>  *HLTOutsideDatasetTriggerNames;
   vector<string>  *HLTFilterName;
   vector<bool>    *HLTInsideDatasetTriggerDecisions;
   vector<bool>    *HLTOutsideDatasetTriggerDecisions;
   vector<double>  *CosmicMuonD0;
   vector<double>  *CosmicMuonDZ;
   vector<double>  *CosmicMuonEta;
   vector<double>  *CosmicMuonPhi;
   vector<double>  *CosmicMuonPt;
   vector<float>   *HBHECosmicDigiEta;
   vector<float>   *HBHECosmicDigiPhi;
   vector<float>   *HBHECosmicDigiRecEnergy;
   vector<float>   *HBHECosmicDigiRecTime;
   vector<float>   *HBHEDigiEta;
   vector<float>   *HBHEDigiPhi;
   vector<float>   *HBHEDigiRecEnergy;
   vector<float>   *HBHEDigiRecTime;
   vector<float>   *HBHERecHitEnergy;
   vector<float>   *HBHERecHitEta;
   vector<float>   *HBHERecHitPhi;
   vector<float>   *HBHERecHitTime;
   vector<float>   *HFDigiEta;
   vector<float>   *HFDigiPhi;
   vector<float>   *HFDigiRecEnergy;
   vector<float>   *HFDigiRecTime;
   vector<float>   *HFRecHitEnergy;
   vector<float>   *HFRecHitEta;
   vector<float>   *HFRecHitPhi;
   vector<float>   *HFRecHitTime;
   vector<float>   *HOCosmicDigiEta;
   vector<float>   *HOCosmicDigiPhi;
   vector<float>   *HOCosmicDigiRecEnergy;
   vector<float>   *HOCosmicDigiRecTime;
   vector<float>   *HODigiEta;
   vector<float>   *HODigiPhi;
   vector<float>   *HODigiRecEnergy;
   vector<float>   *HODigiRecTime;
   vector<float>   *HORecHitEnergy;
   vector<float>   *HORecHitEta;
   vector<float>   *HORecHitPhi;
   vector<float>   *HORecHitTime;
   vector<vector<float> > *HBHECosmicDigiAllFC;
   vector<vector<float> > *HBHECosmicDigiEnergy;
   vector<vector<float> > *HBHECosmicDigiFC;
   vector<vector<float> > *HBHECosmicDigiGain;
   vector<vector<float> > *HBHECosmicDigiNomFC;
   vector<vector<float> > *HBHECosmicDigiPedFC;
   vector<vector<float> > *HBHECosmicDigiRCGain;
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
   vector<vector<float> > *HOCosmicDigiAllFC;
   vector<vector<float> > *HOCosmicDigiEnergy;
   vector<vector<float> > *HOCosmicDigiFC;
   vector<vector<float> > *HOCosmicDigiGain;
   vector<vector<float> > *HOCosmicDigiNomFC;
   vector<vector<float> > *HOCosmicDigiPedFC;
   vector<vector<float> > *HOCosmicDigiRCGain;
   vector<vector<float> > *HODigiAllFC;
   vector<vector<float> > *HODigiEnergy;
   vector<vector<float> > *HODigiFC;
   vector<vector<float> > *HODigiGain;
   vector<vector<float> > *HODigiNomFC;
   vector<vector<float> > *HODigiPedFC;
   vector<vector<float> > *HODigiRCGain;
   vector<vector<float> > *HLTFilterObjEta;
   vector<vector<float> > *HLTFilterObjPhi;
   vector<vector<float> > *HLTFilterObjPt;
   vector<int>     *CosmicMuonNValidHits;
   vector<int>     *FEDBCN;
   vector<int>     *FEDNumber;
   vector<int>     *FEDORN;
   vector<int>     *FEDSize;
   vector<int>     *HBHECosmicDigiDepth;
   vector<int>     *HBHECosmicDigiFiberIdleOffset;
   vector<int>     *HBHECosmicDigiIEta;
   vector<int>     *HBHECosmicDigiIPhi;
   vector<int>     *HBHECosmicDigiPresamples;
   vector<int>     *HBHECosmicDigiSize;
   vector<int>     *HBHEDigiDepth;
   vector<int>     *HBHEDigiFiberIdleOffset;
   vector<int>     *HBHEDigiIEta;
   vector<int>     *HBHEDigiIPhi;
   vector<int>     *HBHEDigiPresamples;
   vector<int>     *HBHEDigiSize;
   vector<int>     *HBHERecHitAux;
   vector<int>     *HBHERecHitDepth;
   vector<int>     *HBHERecHitFlags;
   vector<int>     *HBHERecHitIEta;
   vector<int>     *HBHERecHitIPhi;
   vector<int>     *HFDigiDepth;
   vector<int>     *HFDigiFiberIdleOffset;
   vector<int>     *HFDigiIEta;
   vector<int>     *HFDigiIPhi;
   vector<int>     *HFDigiPresamples;
   vector<int>     *HFDigiSize;
   vector<int>     *HFRecHitAux;
   vector<int>     *HFRecHitDepth;
   vector<int>     *HFRecHitFlags;
   vector<int>     *HFRecHitIEta;
   vector<int>     *HFRecHitIPhi;
   vector<int>     *HOCosmicDigiDepth;
   vector<int>     *HOCosmicDigiFiberIdleOffset;
   vector<int>     *HOCosmicDigiIEta;
   vector<int>     *HOCosmicDigiIPhi;
   vector<int>     *HOCosmicDigiPresamples;
   vector<int>     *HOCosmicDigiSize;
   vector<int>     *HODigiDepth;
   vector<int>     *HODigiFiberIdleOffset;
   vector<int>     *HODigiIEta;
   vector<int>     *HODigiIPhi;
   vector<int>     *HODigiPresamples;
   vector<int>     *HODigiSize;
   vector<int>     *HORecHitAux;
   vector<int>     *HORecHitDepth;
   vector<int>     *HORecHitFlags;
   vector<int>     *HORecHitIEta;
   vector<int>     *HORecHitIPhi;
   vector<int>     *HLTBits;
   vector<int>     *HLTInsideDatasetTriggerPrescales;
   vector<int>     *HLTOutsideDatasetTriggerPrescales;
   vector<int>     *L1PhysBits;
   vector<int>     *L1TechBits;
   vector<vector<int> > *HBHECosmicDigiADC;
   vector<vector<int> > *HBHECosmicDigiCapID;
   vector<vector<int> > *HBHECosmicDigiDV;
   vector<vector<int> > *HBHECosmicDigiER;
   vector<vector<int> > *HBHECosmicDigiFiber;
   vector<vector<int> > *HBHECosmicDigiFiberChan;
   vector<vector<int> > *HBHECosmicDigiRaw;
   vector<vector<int> > *HBHEDigiADC;
   vector<vector<int> > *HBHEDigiCapID;
   vector<vector<int> > *HBHEDigiDV;
   vector<vector<int> > *HBHEDigiER;
   vector<vector<int> > *HBHEDigiFiber;
   vector<vector<int> > *HBHEDigiFiberChan;
   vector<vector<int> > *HBHEDigiRaw;
   vector<vector<int> > *HFDigiADC;
   vector<vector<int> > *HFDigiCapID;
   vector<vector<int> > *HFDigiDV;
   vector<vector<int> > *HFDigiER;
   vector<vector<int> > *HFDigiFiber;
   vector<vector<int> > *HFDigiFiberChan;
   vector<vector<int> > *HFDigiRaw;
   vector<vector<int> > *HOCosmicDigiADC;
   vector<vector<int> > *HOCosmicDigiCapID;
   vector<vector<int> > *HOCosmicDigiDV;
   vector<vector<int> > *HOCosmicDigiER;
   vector<vector<int> > *HOCosmicDigiFiber;
   vector<vector<int> > *HOCosmicDigiFiberChan;
   vector<vector<int> > *HOCosmicDigiRaw;
   vector<vector<int> > *HODigiADC;
   vector<vector<int> > *HODigiCapID;
   vector<vector<int> > *HODigiDV;
   vector<vector<int> > *HODigiER;
   vector<vector<int> > *HODigiFiber;
   vector<vector<int> > *HODigiFiberChan;
   vector<vector<int> > *HODigiRaw;
   vector<vector<int> > *HLTFilterObjId;
   UInt_t          event;
   UInt_t          ls;
   UInt_t          run;

   // List of branches
   TBranch        *b_HLTKey;   //!
   TBranch        *b_HLTInsideDatasetTriggerNames;   //!
   TBranch        *b_HLTOutsideDatasetTriggerNames;   //!
   TBranch        *b_HLTFilterName;   //!
   TBranch        *b_HLTInsideDatasetTriggerDecisions;   //!
   TBranch        *b_HLTOutsideDatasetTriggerDecisions;   //!
   TBranch        *b_CosmicMuonD0;   //!
   TBranch        *b_CosmicMuonDZ;   //!
   TBranch        *b_CosmicMuonEta;   //!
   TBranch        *b_CosmicMuonPhi;   //!
   TBranch        *b_CosmicMuonPt;   //!
   TBranch        *b_HBHECosmicDigiEta;   //!
   TBranch        *b_HBHECosmicDigiPhi;   //!
   TBranch        *b_HBHECosmicDigiRecEnergy;   //!
   TBranch        *b_HBHECosmicDigiRecTime;   //!
   TBranch        *b_HBHEDigiEta;   //!
   TBranch        *b_HBHEDigiPhi;   //!
   TBranch        *b_HBHEDigiRecEnergy;   //!
   TBranch        *b_HBHEDigiRecTime;   //!
   TBranch        *b_HBHERecHitEnergy;   //!
   TBranch        *b_HBHERecHitEta;   //!
   TBranch        *b_HBHERecHitPhi;   //!
   TBranch        *b_HBHERecHitTime;   //!
   TBranch        *b_HFDigiEta;   //!
   TBranch        *b_HFDigiPhi;   //!
   TBranch        *b_HFDigiRecEnergy;   //!
   TBranch        *b_HFDigiRecTime;   //!
   TBranch        *b_HFRecHitEnergy;   //!
   TBranch        *b_HFRecHitEta;   //!
   TBranch        *b_HFRecHitPhi;   //!
   TBranch        *b_HFRecHitTime;   //!
   TBranch        *b_HOCosmicDigiEta;   //!
   TBranch        *b_HOCosmicDigiPhi;   //!
   TBranch        *b_HOCosmicDigiRecEnergy;   //!
   TBranch        *b_HOCosmicDigiRecTime;   //!
   TBranch        *b_HODigiEta;   //!
   TBranch        *b_HODigiPhi;   //!
   TBranch        *b_HODigiRecEnergy;   //!
   TBranch        *b_HODigiRecTime;   //!
   TBranch        *b_HORecHitEnergy;   //!
   TBranch        *b_HORecHitEta;   //!
   TBranch        *b_HORecHitPhi;   //!
   TBranch        *b_HORecHitTime;   //!
   TBranch        *b_HBHECosmicDigiAllFC;   //!
   TBranch        *b_HBHECosmicDigiEnergy;   //!
   TBranch        *b_HBHECosmicDigiFC;   //!
   TBranch        *b_HBHECosmicDigiGain;   //!
   TBranch        *b_HBHECosmicDigiNomFC;   //!
   TBranch        *b_HBHECosmicDigiPedFC;   //!
   TBranch        *b_HBHECosmicDigiRCGain;   //!
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
   TBranch        *b_HOCosmicDigiAllFC;   //!
   TBranch        *b_HOCosmicDigiEnergy;   //!
   TBranch        *b_HOCosmicDigiFC;   //!
   TBranch        *b_HOCosmicDigiGain;   //!
   TBranch        *b_HOCosmicDigiNomFC;   //!
   TBranch        *b_HOCosmicDigiPedFC;   //!
   TBranch        *b_HOCosmicDigiRCGain;   //!
   TBranch        *b_HODigiAllFC;   //!
   TBranch        *b_HODigiEnergy;   //!
   TBranch        *b_HODigiFC;   //!
   TBranch        *b_HODigiGain;   //!
   TBranch        *b_HODigiNomFC;   //!
   TBranch        *b_HODigiPedFC;   //!
   TBranch        *b_HODigiRCGain;   //!
   TBranch        *b_HLTFilterObjEta;   //!
   TBranch        *b_HLTFilterObjPhi;   //!
   TBranch        *b_HLTFilterObjPt;   //!
   TBranch        *b_CosmicMuonNValidHits;   //!
   TBranch        *b_FEDBCN;   //!
   TBranch        *b_FEDNumber;   //!
   TBranch        *b_FEDORN;   //!
   TBranch        *b_FEDSize;   //!
   TBranch        *b_HBHECosmicDigiDepth;   //!
   TBranch        *b_HBHECosmicDigiFiberIdleOffset;   //!
   TBranch        *b_HBHECosmicDigiIEta;   //!
   TBranch        *b_HBHECosmicDigiIPhi;   //!
   TBranch        *b_HBHECosmicDigiPresamples;   //!
   TBranch        *b_HBHECosmicDigiSize;   //!
   TBranch        *b_HBHEDigiDepth;   //!
   TBranch        *b_HBHEDigiFiberIdleOffset;   //!
   TBranch        *b_HBHEDigiIEta;   //!
   TBranch        *b_HBHEDigiIPhi;   //!
   TBranch        *b_HBHEDigiPresamples;   //!
   TBranch        *b_HBHEDigiSize;   //!
   TBranch        *b_HBHERecHitAux;   //!
   TBranch        *b_HBHERecHitDepth;   //!
   TBranch        *b_HBHERecHitFlags;   //!
   TBranch        *b_HBHERecHitIEta;   //!
   TBranch        *b_HBHERecHitIPhi;   //!
   TBranch        *b_HFDigiDepth;   //!
   TBranch        *b_HFDigiFiberIdleOffset;   //!
   TBranch        *b_HFDigiIEta;   //!
   TBranch        *b_HFDigiIPhi;   //!
   TBranch        *b_HFDigiPresamples;   //!
   TBranch        *b_HFDigiSize;   //!
   TBranch        *b_HFRecHitAux;   //!
   TBranch        *b_HFRecHitDepth;   //!
   TBranch        *b_HFRecHitFlags;   //!
   TBranch        *b_HFRecHitIEta;   //!
   TBranch        *b_HFRecHitIPhi;   //!
   TBranch        *b_HOCosmicDigiDepth;   //!
   TBranch        *b_HOCosmicDigiFiberIdleOffset;   //!
   TBranch        *b_HOCosmicDigiIEta;   //!
   TBranch        *b_HOCosmicDigiIPhi;   //!
   TBranch        *b_HOCosmicDigiPresamples;   //!
   TBranch        *b_HOCosmicDigiSize;   //!
   TBranch        *b_HODigiDepth;   //!
   TBranch        *b_HODigiFiberIdleOffset;   //!
   TBranch        *b_HODigiIEta;   //!
   TBranch        *b_HODigiIPhi;   //!
   TBranch        *b_HODigiPresamples;   //!
   TBranch        *b_HODigiSize;   //!
   TBranch        *b_HORecHitAux;   //!
   TBranch        *b_HORecHitDepth;   //!
   TBranch        *b_HORecHitFlags;   //!
   TBranch        *b_HORecHitIEta;   //!
   TBranch        *b_HORecHitIPhi;   //!
   TBranch        *b_HLTBits;   //!
   TBranch        *b_HLTInsideDatasetTriggerPrescales;   //!
   TBranch        *b_HLTOutsideDatasetTriggerPrescales;   //!
   TBranch        *b_L1PhysBits;   //!
   TBranch        *b_L1TechBits;   //!
   TBranch        *b_HBHECosmicDigiADC;   //!
   TBranch        *b_HBHECosmicDigiCapID;   //!
   TBranch        *b_HBHECosmicDigiDV;   //!
   TBranch        *b_HBHECosmicDigiER;   //!
   TBranch        *b_HBHECosmicDigiFiber;   //!
   TBranch        *b_HBHECosmicDigiFiberChan;   //!
   TBranch        *b_HBHECosmicDigiRaw;   //!
   TBranch        *b_HBHEDigiADC;   //!
   TBranch        *b_HBHEDigiCapID;   //!
   TBranch        *b_HBHEDigiDV;   //!
   TBranch        *b_HBHEDigiER;   //!
   TBranch        *b_HBHEDigiFiber;   //!
   TBranch        *b_HBHEDigiFiberChan;   //!
   TBranch        *b_HBHEDigiRaw;   //!
   TBranch        *b_HFDigiADC;   //!
   TBranch        *b_HFDigiCapID;   //!
   TBranch        *b_HFDigiDV;   //!
   TBranch        *b_HFDigiER;   //!
   TBranch        *b_HFDigiFiber;   //!
   TBranch        *b_HFDigiFiberChan;   //!
   TBranch        *b_HFDigiRaw;   //!
   TBranch        *b_HOCosmicDigiADC;   //!
   TBranch        *b_HOCosmicDigiCapID;   //!
   TBranch        *b_HOCosmicDigiDV;   //!
   TBranch        *b_HOCosmicDigiER;   //!
   TBranch        *b_HOCosmicDigiFiber;   //!
   TBranch        *b_HOCosmicDigiFiberChan;   //!
   TBranch        *b_HOCosmicDigiRaw;   //!
   TBranch        *b_HODigiADC;   //!
   TBranch        *b_HODigiCapID;   //!
   TBranch        *b_HODigiDV;   //!
   TBranch        *b_HODigiER;   //!
   TBranch        *b_HODigiFiber;   //!
   TBranch        *b_HODigiFiberChan;   //!
   TBranch        *b_HODigiRaw;   //!
   TBranch        *b_HLTFilterObjId;   //!
   TBranch        *b_event;   //!
   TBranch        *b_ls;   //!
   TBranch        *b_run;   //!

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
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("root://eoscms//eos/cms/store/user/eberry/HCALPFG/MWGR8_227391_HcalHPDNoise_v3/MWGR8_227391_HcalHPDNoise_0.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("root://eoscms//eos/cms/store/user/eberry/HCALPFG/MWGR8_227391_HcalHPDNoise_v3/MWGR8_227391_HcalHPDNoise_0.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("root://eoscms//eos/cms/store/user/eberry/HCALPFG/MWGR8_227391_HcalHPDNoise_v3/MWGR8_227391_HcalHPDNoise_0.root:/hcalTupleTree");
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
   HLTKey = 0;
   HLTInsideDatasetTriggerNames = 0;
   HLTOutsideDatasetTriggerNames = 0;
   HLTFilterName = 0;
   HLTInsideDatasetTriggerDecisions = 0;
   HLTOutsideDatasetTriggerDecisions = 0;
   CosmicMuonD0 = 0;
   CosmicMuonDZ = 0;
   CosmicMuonEta = 0;
   CosmicMuonPhi = 0;
   CosmicMuonPt = 0;
   HBHECosmicDigiEta = 0;
   HBHECosmicDigiPhi = 0;
   HBHECosmicDigiRecEnergy = 0;
   HBHECosmicDigiRecTime = 0;
   HBHEDigiEta = 0;
   HBHEDigiPhi = 0;
   HBHEDigiRecEnergy = 0;
   HBHEDigiRecTime = 0;
   HBHERecHitEnergy = 0;
   HBHERecHitEta = 0;
   HBHERecHitPhi = 0;
   HBHERecHitTime = 0;
   HFDigiEta = 0;
   HFDigiPhi = 0;
   HFDigiRecEnergy = 0;
   HFDigiRecTime = 0;
   HFRecHitEnergy = 0;
   HFRecHitEta = 0;
   HFRecHitPhi = 0;
   HFRecHitTime = 0;
   HOCosmicDigiEta = 0;
   HOCosmicDigiPhi = 0;
   HOCosmicDigiRecEnergy = 0;
   HOCosmicDigiRecTime = 0;
   HODigiEta = 0;
   HODigiPhi = 0;
   HODigiRecEnergy = 0;
   HODigiRecTime = 0;
   HORecHitEnergy = 0;
   HORecHitEta = 0;
   HORecHitPhi = 0;
   HORecHitTime = 0;
   HBHECosmicDigiAllFC = 0;
   HBHECosmicDigiEnergy = 0;
   HBHECosmicDigiFC = 0;
   HBHECosmicDigiGain = 0;
   HBHECosmicDigiNomFC = 0;
   HBHECosmicDigiPedFC = 0;
   HBHECosmicDigiRCGain = 0;
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
   HOCosmicDigiAllFC = 0;
   HOCosmicDigiEnergy = 0;
   HOCosmicDigiFC = 0;
   HOCosmicDigiGain = 0;
   HOCosmicDigiNomFC = 0;
   HOCosmicDigiPedFC = 0;
   HOCosmicDigiRCGain = 0;
   HODigiAllFC = 0;
   HODigiEnergy = 0;
   HODigiFC = 0;
   HODigiGain = 0;
   HODigiNomFC = 0;
   HODigiPedFC = 0;
   HODigiRCGain = 0;
   HLTFilterObjEta = 0;
   HLTFilterObjPhi = 0;
   HLTFilterObjPt = 0;
   CosmicMuonNValidHits = 0;
   FEDBCN = 0;
   FEDNumber = 0;
   FEDORN = 0;
   FEDSize = 0;
   HBHECosmicDigiDepth = 0;
   HBHECosmicDigiFiberIdleOffset = 0;
   HBHECosmicDigiIEta = 0;
   HBHECosmicDigiIPhi = 0;
   HBHECosmicDigiPresamples = 0;
   HBHECosmicDigiSize = 0;
   HBHEDigiDepth = 0;
   HBHEDigiFiberIdleOffset = 0;
   HBHEDigiIEta = 0;
   HBHEDigiIPhi = 0;
   HBHEDigiPresamples = 0;
   HBHEDigiSize = 0;
   HBHERecHitAux = 0;
   HBHERecHitDepth = 0;
   HBHERecHitFlags = 0;
   HBHERecHitIEta = 0;
   HBHERecHitIPhi = 0;
   HFDigiDepth = 0;
   HFDigiFiberIdleOffset = 0;
   HFDigiIEta = 0;
   HFDigiIPhi = 0;
   HFDigiPresamples = 0;
   HFDigiSize = 0;
   HFRecHitAux = 0;
   HFRecHitDepth = 0;
   HFRecHitFlags = 0;
   HFRecHitIEta = 0;
   HFRecHitIPhi = 0;
   HOCosmicDigiDepth = 0;
   HOCosmicDigiFiberIdleOffset = 0;
   HOCosmicDigiIEta = 0;
   HOCosmicDigiIPhi = 0;
   HOCosmicDigiPresamples = 0;
   HOCosmicDigiSize = 0;
   HODigiDepth = 0;
   HODigiFiberIdleOffset = 0;
   HODigiIEta = 0;
   HODigiIPhi = 0;
   HODigiPresamples = 0;
   HODigiSize = 0;
   HORecHitAux = 0;
   HORecHitDepth = 0;
   HORecHitFlags = 0;
   HORecHitIEta = 0;
   HORecHitIPhi = 0;
   HLTBits = 0;
   HLTInsideDatasetTriggerPrescales = 0;
   HLTOutsideDatasetTriggerPrescales = 0;
   L1PhysBits = 0;
   L1TechBits = 0;
   HBHECosmicDigiADC = 0;
   HBHECosmicDigiCapID = 0;
   HBHECosmicDigiDV = 0;
   HBHECosmicDigiER = 0;
   HBHECosmicDigiFiber = 0;
   HBHECosmicDigiFiberChan = 0;
   HBHECosmicDigiRaw = 0;
   HBHEDigiADC = 0;
   HBHEDigiCapID = 0;
   HBHEDigiDV = 0;
   HBHEDigiER = 0;
   HBHEDigiFiber = 0;
   HBHEDigiFiberChan = 0;
   HBHEDigiRaw = 0;
   HFDigiADC = 0;
   HFDigiCapID = 0;
   HFDigiDV = 0;
   HFDigiER = 0;
   HFDigiFiber = 0;
   HFDigiFiberChan = 0;
   HFDigiRaw = 0;
   HOCosmicDigiADC = 0;
   HOCosmicDigiCapID = 0;
   HOCosmicDigiDV = 0;
   HOCosmicDigiER = 0;
   HOCosmicDigiFiber = 0;
   HOCosmicDigiFiberChan = 0;
   HOCosmicDigiRaw = 0;
   HODigiADC = 0;
   HODigiCapID = 0;
   HODigiDV = 0;
   HODigiER = 0;
   HODigiFiber = 0;
   HODigiFiberChan = 0;
   HODigiRaw = 0;
   HLTFilterObjId = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("HLTKey", &HLTKey, &b_HLTKey);
   fChain->SetBranchAddress("HLTInsideDatasetTriggerNames", &HLTInsideDatasetTriggerNames, &b_HLTInsideDatasetTriggerNames);
   fChain->SetBranchAddress("HLTOutsideDatasetTriggerNames", &HLTOutsideDatasetTriggerNames, &b_HLTOutsideDatasetTriggerNames);
   fChain->SetBranchAddress("HLTFilterName", &HLTFilterName, &b_HLTFilterName);
   fChain->SetBranchAddress("HLTInsideDatasetTriggerDecisions", &HLTInsideDatasetTriggerDecisions, &b_HLTInsideDatasetTriggerDecisions);
   fChain->SetBranchAddress("HLTOutsideDatasetTriggerDecisions", &HLTOutsideDatasetTriggerDecisions, &b_HLTOutsideDatasetTriggerDecisions);
   fChain->SetBranchAddress("CosmicMuonD0", &CosmicMuonD0, &b_CosmicMuonD0);
   fChain->SetBranchAddress("CosmicMuonDZ", &CosmicMuonDZ, &b_CosmicMuonDZ);
   fChain->SetBranchAddress("CosmicMuonEta", &CosmicMuonEta, &b_CosmicMuonEta);
   fChain->SetBranchAddress("CosmicMuonPhi", &CosmicMuonPhi, &b_CosmicMuonPhi);
   fChain->SetBranchAddress("CosmicMuonPt", &CosmicMuonPt, &b_CosmicMuonPt);
   fChain->SetBranchAddress("HBHECosmicDigiEta", &HBHECosmicDigiEta, &b_HBHECosmicDigiEta);
   fChain->SetBranchAddress("HBHECosmicDigiPhi", &HBHECosmicDigiPhi, &b_HBHECosmicDigiPhi);
   fChain->SetBranchAddress("HBHECosmicDigiRecEnergy", &HBHECosmicDigiRecEnergy, &b_HBHECosmicDigiRecEnergy);
   fChain->SetBranchAddress("HBHECosmicDigiRecTime", &HBHECosmicDigiRecTime, &b_HBHECosmicDigiRecTime);
   fChain->SetBranchAddress("HBHEDigiEta", &HBHEDigiEta, &b_HBHEDigiEta);
   fChain->SetBranchAddress("HBHEDigiPhi", &HBHEDigiPhi, &b_HBHEDigiPhi);
   fChain->SetBranchAddress("HBHEDigiRecEnergy", &HBHEDigiRecEnergy, &b_HBHEDigiRecEnergy);
   fChain->SetBranchAddress("HBHEDigiRecTime", &HBHEDigiRecTime, &b_HBHEDigiRecTime);
   fChain->SetBranchAddress("HBHERecHitEnergy", &HBHERecHitEnergy, &b_HBHERecHitEnergy);
   fChain->SetBranchAddress("HBHERecHitEta", &HBHERecHitEta, &b_HBHERecHitEta);
   fChain->SetBranchAddress("HBHERecHitPhi", &HBHERecHitPhi, &b_HBHERecHitPhi);
   fChain->SetBranchAddress("HBHERecHitTime", &HBHERecHitTime, &b_HBHERecHitTime);
   fChain->SetBranchAddress("HFDigiEta", &HFDigiEta, &b_HFDigiEta);
   fChain->SetBranchAddress("HFDigiPhi", &HFDigiPhi, &b_HFDigiPhi);
   fChain->SetBranchAddress("HFDigiRecEnergy", &HFDigiRecEnergy, &b_HFDigiRecEnergy);
   fChain->SetBranchAddress("HFDigiRecTime", &HFDigiRecTime, &b_HFDigiRecTime);
   fChain->SetBranchAddress("HFRecHitEnergy", &HFRecHitEnergy, &b_HFRecHitEnergy);
   fChain->SetBranchAddress("HFRecHitEta", &HFRecHitEta, &b_HFRecHitEta);
   fChain->SetBranchAddress("HFRecHitPhi", &HFRecHitPhi, &b_HFRecHitPhi);
   fChain->SetBranchAddress("HFRecHitTime", &HFRecHitTime, &b_HFRecHitTime);
   fChain->SetBranchAddress("HOCosmicDigiEta", &HOCosmicDigiEta, &b_HOCosmicDigiEta);
   fChain->SetBranchAddress("HOCosmicDigiPhi", &HOCosmicDigiPhi, &b_HOCosmicDigiPhi);
   fChain->SetBranchAddress("HOCosmicDigiRecEnergy", &HOCosmicDigiRecEnergy, &b_HOCosmicDigiRecEnergy);
   fChain->SetBranchAddress("HOCosmicDigiRecTime", &HOCosmicDigiRecTime, &b_HOCosmicDigiRecTime);
   fChain->SetBranchAddress("HODigiEta", &HODigiEta, &b_HODigiEta);
   fChain->SetBranchAddress("HODigiPhi", &HODigiPhi, &b_HODigiPhi);
   fChain->SetBranchAddress("HODigiRecEnergy", &HODigiRecEnergy, &b_HODigiRecEnergy);
   fChain->SetBranchAddress("HODigiRecTime", &HODigiRecTime, &b_HODigiRecTime);
   fChain->SetBranchAddress("HORecHitEnergy", &HORecHitEnergy, &b_HORecHitEnergy);
   fChain->SetBranchAddress("HORecHitEta", &HORecHitEta, &b_HORecHitEta);
   fChain->SetBranchAddress("HORecHitPhi", &HORecHitPhi, &b_HORecHitPhi);
   fChain->SetBranchAddress("HORecHitTime", &HORecHitTime, &b_HORecHitTime);
   fChain->SetBranchAddress("HBHECosmicDigiAllFC", &HBHECosmicDigiAllFC, &b_HBHECosmicDigiAllFC);
   fChain->SetBranchAddress("HBHECosmicDigiEnergy", &HBHECosmicDigiEnergy, &b_HBHECosmicDigiEnergy);
   fChain->SetBranchAddress("HBHECosmicDigiFC", &HBHECosmicDigiFC, &b_HBHECosmicDigiFC);
   fChain->SetBranchAddress("HBHECosmicDigiGain", &HBHECosmicDigiGain, &b_HBHECosmicDigiGain);
   fChain->SetBranchAddress("HBHECosmicDigiNomFC", &HBHECosmicDigiNomFC, &b_HBHECosmicDigiNomFC);
   fChain->SetBranchAddress("HBHECosmicDigiPedFC", &HBHECosmicDigiPedFC, &b_HBHECosmicDigiPedFC);
   fChain->SetBranchAddress("HBHECosmicDigiRCGain", &HBHECosmicDigiRCGain, &b_HBHECosmicDigiRCGain);
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
   fChain->SetBranchAddress("HOCosmicDigiAllFC", &HOCosmicDigiAllFC, &b_HOCosmicDigiAllFC);
   fChain->SetBranchAddress("HOCosmicDigiEnergy", &HOCosmicDigiEnergy, &b_HOCosmicDigiEnergy);
   fChain->SetBranchAddress("HOCosmicDigiFC", &HOCosmicDigiFC, &b_HOCosmicDigiFC);
   fChain->SetBranchAddress("HOCosmicDigiGain", &HOCosmicDigiGain, &b_HOCosmicDigiGain);
   fChain->SetBranchAddress("HOCosmicDigiNomFC", &HOCosmicDigiNomFC, &b_HOCosmicDigiNomFC);
   fChain->SetBranchAddress("HOCosmicDigiPedFC", &HOCosmicDigiPedFC, &b_HOCosmicDigiPedFC);
   fChain->SetBranchAddress("HOCosmicDigiRCGain", &HOCosmicDigiRCGain, &b_HOCosmicDigiRCGain);
   fChain->SetBranchAddress("HODigiAllFC", &HODigiAllFC, &b_HODigiAllFC);
   fChain->SetBranchAddress("HODigiEnergy", &HODigiEnergy, &b_HODigiEnergy);
   fChain->SetBranchAddress("HODigiFC", &HODigiFC, &b_HODigiFC);
   fChain->SetBranchAddress("HODigiGain", &HODigiGain, &b_HODigiGain);
   fChain->SetBranchAddress("HODigiNomFC", &HODigiNomFC, &b_HODigiNomFC);
   fChain->SetBranchAddress("HODigiPedFC", &HODigiPedFC, &b_HODigiPedFC);
   fChain->SetBranchAddress("HODigiRCGain", &HODigiRCGain, &b_HODigiRCGain);
   fChain->SetBranchAddress("HLTFilterObjEta", &HLTFilterObjEta, &b_HLTFilterObjEta);
   fChain->SetBranchAddress("HLTFilterObjPhi", &HLTFilterObjPhi, &b_HLTFilterObjPhi);
   fChain->SetBranchAddress("HLTFilterObjPt", &HLTFilterObjPt, &b_HLTFilterObjPt);
   fChain->SetBranchAddress("CosmicMuonNValidHits", &CosmicMuonNValidHits, &b_CosmicMuonNValidHits);
   fChain->SetBranchAddress("FEDBCN", &FEDBCN, &b_FEDBCN);
   fChain->SetBranchAddress("FEDNumber", &FEDNumber, &b_FEDNumber);
   fChain->SetBranchAddress("FEDORN", &FEDORN, &b_FEDORN);
   fChain->SetBranchAddress("FEDSize", &FEDSize, &b_FEDSize);
   fChain->SetBranchAddress("HBHECosmicDigiDepth", &HBHECosmicDigiDepth, &b_HBHECosmicDigiDepth);
   fChain->SetBranchAddress("HBHECosmicDigiFiberIdleOffset", &HBHECosmicDigiFiberIdleOffset, &b_HBHECosmicDigiFiberIdleOffset);
   fChain->SetBranchAddress("HBHECosmicDigiIEta", &HBHECosmicDigiIEta, &b_HBHECosmicDigiIEta);
   fChain->SetBranchAddress("HBHECosmicDigiIPhi", &HBHECosmicDigiIPhi, &b_HBHECosmicDigiIPhi);
   fChain->SetBranchAddress("HBHECosmicDigiPresamples", &HBHECosmicDigiPresamples, &b_HBHECosmicDigiPresamples);
   fChain->SetBranchAddress("HBHECosmicDigiSize", &HBHECosmicDigiSize, &b_HBHECosmicDigiSize);
   fChain->SetBranchAddress("HBHEDigiDepth", &HBHEDigiDepth, &b_HBHEDigiDepth);
   fChain->SetBranchAddress("HBHEDigiFiberIdleOffset", &HBHEDigiFiberIdleOffset, &b_HBHEDigiFiberIdleOffset);
   fChain->SetBranchAddress("HBHEDigiIEta", &HBHEDigiIEta, &b_HBHEDigiIEta);
   fChain->SetBranchAddress("HBHEDigiIPhi", &HBHEDigiIPhi, &b_HBHEDigiIPhi);
   fChain->SetBranchAddress("HBHEDigiPresamples", &HBHEDigiPresamples, &b_HBHEDigiPresamples);
   fChain->SetBranchAddress("HBHEDigiSize", &HBHEDigiSize, &b_HBHEDigiSize);
   fChain->SetBranchAddress("HBHERecHitAux", &HBHERecHitAux, &b_HBHERecHitAux);
   fChain->SetBranchAddress("HBHERecHitDepth", &HBHERecHitDepth, &b_HBHERecHitDepth);
   fChain->SetBranchAddress("HBHERecHitFlags", &HBHERecHitFlags, &b_HBHERecHitFlags);
   fChain->SetBranchAddress("HBHERecHitIEta", &HBHERecHitIEta, &b_HBHERecHitIEta);
   fChain->SetBranchAddress("HBHERecHitIPhi", &HBHERecHitIPhi, &b_HBHERecHitIPhi);
   fChain->SetBranchAddress("HFDigiDepth", &HFDigiDepth, &b_HFDigiDepth);
   fChain->SetBranchAddress("HFDigiFiberIdleOffset", &HFDigiFiberIdleOffset, &b_HFDigiFiberIdleOffset);
   fChain->SetBranchAddress("HFDigiIEta", &HFDigiIEta, &b_HFDigiIEta);
   fChain->SetBranchAddress("HFDigiIPhi", &HFDigiIPhi, &b_HFDigiIPhi);
   fChain->SetBranchAddress("HFDigiPresamples", &HFDigiPresamples, &b_HFDigiPresamples);
   fChain->SetBranchAddress("HFDigiSize", &HFDigiSize, &b_HFDigiSize);
   fChain->SetBranchAddress("HFRecHitAux", &HFRecHitAux, &b_HFRecHitAux);
   fChain->SetBranchAddress("HFRecHitDepth", &HFRecHitDepth, &b_HFRecHitDepth);
   fChain->SetBranchAddress("HFRecHitFlags", &HFRecHitFlags, &b_HFRecHitFlags);
   fChain->SetBranchAddress("HFRecHitIEta", &HFRecHitIEta, &b_HFRecHitIEta);
   fChain->SetBranchAddress("HFRecHitIPhi", &HFRecHitIPhi, &b_HFRecHitIPhi);
   fChain->SetBranchAddress("HOCosmicDigiDepth", &HOCosmicDigiDepth, &b_HOCosmicDigiDepth);
   fChain->SetBranchAddress("HOCosmicDigiFiberIdleOffset", &HOCosmicDigiFiberIdleOffset, &b_HOCosmicDigiFiberIdleOffset);
   fChain->SetBranchAddress("HOCosmicDigiIEta", &HOCosmicDigiIEta, &b_HOCosmicDigiIEta);
   fChain->SetBranchAddress("HOCosmicDigiIPhi", &HOCosmicDigiIPhi, &b_HOCosmicDigiIPhi);
   fChain->SetBranchAddress("HOCosmicDigiPresamples", &HOCosmicDigiPresamples, &b_HOCosmicDigiPresamples);
   fChain->SetBranchAddress("HOCosmicDigiSize", &HOCosmicDigiSize, &b_HOCosmicDigiSize);
   fChain->SetBranchAddress("HODigiDepth", &HODigiDepth, &b_HODigiDepth);
   fChain->SetBranchAddress("HODigiFiberIdleOffset", &HODigiFiberIdleOffset, &b_HODigiFiberIdleOffset);
   fChain->SetBranchAddress("HODigiIEta", &HODigiIEta, &b_HODigiIEta);
   fChain->SetBranchAddress("HODigiIPhi", &HODigiIPhi, &b_HODigiIPhi);
   fChain->SetBranchAddress("HODigiPresamples", &HODigiPresamples, &b_HODigiPresamples);
   fChain->SetBranchAddress("HODigiSize", &HODigiSize, &b_HODigiSize);
   fChain->SetBranchAddress("HORecHitAux", &HORecHitAux, &b_HORecHitAux);
   fChain->SetBranchAddress("HORecHitDepth", &HORecHitDepth, &b_HORecHitDepth);
   fChain->SetBranchAddress("HORecHitFlags", &HORecHitFlags, &b_HORecHitFlags);
   fChain->SetBranchAddress("HORecHitIEta", &HORecHitIEta, &b_HORecHitIEta);
   fChain->SetBranchAddress("HORecHitIPhi", &HORecHitIPhi, &b_HORecHitIPhi);
   fChain->SetBranchAddress("HLTBits", &HLTBits, &b_HLTBits);
   fChain->SetBranchAddress("HLTInsideDatasetTriggerPrescales", &HLTInsideDatasetTriggerPrescales, &b_HLTInsideDatasetTriggerPrescales);
   fChain->SetBranchAddress("HLTOutsideDatasetTriggerPrescales", &HLTOutsideDatasetTriggerPrescales, &b_HLTOutsideDatasetTriggerPrescales);
   fChain->SetBranchAddress("L1PhysBits", &L1PhysBits, &b_L1PhysBits);
   fChain->SetBranchAddress("L1TechBits", &L1TechBits, &b_L1TechBits);
   fChain->SetBranchAddress("HBHECosmicDigiADC", &HBHECosmicDigiADC, &b_HBHECosmicDigiADC);
   fChain->SetBranchAddress("HBHECosmicDigiCapID", &HBHECosmicDigiCapID, &b_HBHECosmicDigiCapID);
   fChain->SetBranchAddress("HBHECosmicDigiDV", &HBHECosmicDigiDV, &b_HBHECosmicDigiDV);
   fChain->SetBranchAddress("HBHECosmicDigiER", &HBHECosmicDigiER, &b_HBHECosmicDigiER);
   fChain->SetBranchAddress("HBHECosmicDigiFiber", &HBHECosmicDigiFiber, &b_HBHECosmicDigiFiber);
   fChain->SetBranchAddress("HBHECosmicDigiFiberChan", &HBHECosmicDigiFiberChan, &b_HBHECosmicDigiFiberChan);
   fChain->SetBranchAddress("HBHECosmicDigiRaw", &HBHECosmicDigiRaw, &b_HBHECosmicDigiRaw);
   fChain->SetBranchAddress("HBHEDigiADC", &HBHEDigiADC, &b_HBHEDigiADC);
   fChain->SetBranchAddress("HBHEDigiCapID", &HBHEDigiCapID, &b_HBHEDigiCapID);
   fChain->SetBranchAddress("HBHEDigiDV", &HBHEDigiDV, &b_HBHEDigiDV);
   fChain->SetBranchAddress("HBHEDigiER", &HBHEDigiER, &b_HBHEDigiER);
   fChain->SetBranchAddress("HBHEDigiFiber", &HBHEDigiFiber, &b_HBHEDigiFiber);
   fChain->SetBranchAddress("HBHEDigiFiberChan", &HBHEDigiFiberChan, &b_HBHEDigiFiberChan);
   fChain->SetBranchAddress("HBHEDigiRaw", &HBHEDigiRaw, &b_HBHEDigiRaw);
   fChain->SetBranchAddress("HFDigiADC", &HFDigiADC, &b_HFDigiADC);
   fChain->SetBranchAddress("HFDigiCapID", &HFDigiCapID, &b_HFDigiCapID);
   fChain->SetBranchAddress("HFDigiDV", &HFDigiDV, &b_HFDigiDV);
   fChain->SetBranchAddress("HFDigiER", &HFDigiER, &b_HFDigiER);
   fChain->SetBranchAddress("HFDigiFiber", &HFDigiFiber, &b_HFDigiFiber);
   fChain->SetBranchAddress("HFDigiFiberChan", &HFDigiFiberChan, &b_HFDigiFiberChan);
   fChain->SetBranchAddress("HFDigiRaw", &HFDigiRaw, &b_HFDigiRaw);
   fChain->SetBranchAddress("HOCosmicDigiADC", &HOCosmicDigiADC, &b_HOCosmicDigiADC);
   fChain->SetBranchAddress("HOCosmicDigiCapID", &HOCosmicDigiCapID, &b_HOCosmicDigiCapID);
   fChain->SetBranchAddress("HOCosmicDigiDV", &HOCosmicDigiDV, &b_HOCosmicDigiDV);
   fChain->SetBranchAddress("HOCosmicDigiER", &HOCosmicDigiER, &b_HOCosmicDigiER);
   fChain->SetBranchAddress("HOCosmicDigiFiber", &HOCosmicDigiFiber, &b_HOCosmicDigiFiber);
   fChain->SetBranchAddress("HOCosmicDigiFiberChan", &HOCosmicDigiFiberChan, &b_HOCosmicDigiFiberChan);
   fChain->SetBranchAddress("HOCosmicDigiRaw", &HOCosmicDigiRaw, &b_HOCosmicDigiRaw);
   fChain->SetBranchAddress("HODigiADC", &HODigiADC, &b_HODigiADC);
   fChain->SetBranchAddress("HODigiCapID", &HODigiCapID, &b_HODigiCapID);
   fChain->SetBranchAddress("HODigiDV", &HODigiDV, &b_HODigiDV);
   fChain->SetBranchAddress("HODigiER", &HODigiER, &b_HODigiER);
   fChain->SetBranchAddress("HODigiFiber", &HODigiFiber, &b_HODigiFiber);
   fChain->SetBranchAddress("HODigiFiberChan", &HODigiFiberChan, &b_HODigiFiberChan);
   fChain->SetBranchAddress("HODigiRaw", &HODigiRaw, &b_HODigiRaw);
   fChain->SetBranchAddress("HLTFilterObjId", &HLTFilterObjId, &b_HLTFilterObjId);
   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("ls", &ls, &b_ls);
   fChain->SetBranchAddress("run", &run, &b_run);
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
