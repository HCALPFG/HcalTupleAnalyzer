#include "TFile.h"
#include "TH2F.h"
#include "TProfile.h"
#include "TF1.h"
#include "TMath.h"

Double_t fitf ( Double_t * x , Double_t * par ) { 
  Double_t xx        = x  [0];
  Double_t offset    = par[0];
  Double_t amplitude = par[1];
  Double_t frequency = par[2];
  Double_t phase     = par[3];
  Double_t retval    = offset + amplitude * TMath::Sin( frequency * xx + phase );
  return retval;
}

void fit_timing_study(){

  gStyle -> SetOptFit(1);
  gStyle -> SetOptStat(0);
  gStyle -> SetOptTitle(0);

  // TFile    * file = new TFile("/mnt/lxplus/work/HCALPFG/CMSSW_7_1_7/src/HCALPFG/HcalTupleAnalyzer/output/output_ECR_229713_Cosmics.root");
  // TH2F     * hist = (TH2F*) file -> Get("hb_cosmic_phi_vs_timing_depth1_dtFired");
  
  // TFile    * file = new TFile("/mnt/lxplus/work/HCALPFG/CMSSW_7_1_7/src/HCALPFG/HcalTupleAnalyzer/output/output_ECR_231228_Cosmics.root");
  TFile    * file = new TFile("ExpressCosmics_EMapUpdated.root");
  TH2F     * hist = (TH2F*) file -> Get("hbhe_cosmic_phi_vs_timing_depth1_dtFired");
  // TH2F     * hist = (TH2F*) file -> Get("ho_cosmic_phi_vs_timing_dtFired");
  TProfile * prof = (TProfile*) hist -> ProfileX();
  TF1      * func = new TF1("func", fitf, -3.1416, 3.1416, 4);
  TCanvas  * canv = new TCanvas();

  canv -> cd();

  prof -> SetMinimum(0.0);
  prof -> SetMaximum(10.0);
  prof -> GetXaxis() -> SetTitle("HBHE RecHit #phi");
  prof -> GetYaxis() -> SetTitle("HBHE RecHit timing");
  hist -> GetXaxis() -> SetTitle("HBHE RecHit #phi");
  hist -> GetYaxis() -> SetTitle("HBHE RecHit timing");

  func -> SetParName(0, "<Time>");
  func -> SetParName(1, "Amplitude");
  func -> SetParName(2, "Frequency");
  func -> SetParName(3, "Phase");
  
  func -> SetParLimits(0, 0.0, 10.0);
  func -> SetParLimits(1, 0.1, 2.0);
  func -> SetParLimits(2, 0.5, 2.0);
  func -> SetParLimits(3, 0.0, 2.0 * TMath::Pi());
  
  func -> SetParameter(0, 4.0);
  func -> SetParameter(1, 0.5);
  func -> SetParameter(2, 1.0);
  func -> SetParameter(3, TMath::Pi());

  prof -> Fit("func");
  prof -> Draw();
  func -> Draw("SAME");
  
  canv -> Update();
  double xmin = canv -> GetUxmin();
  double xmax = canv -> GetUxmax();
  double ymin = canv -> GetUymin();
  double ymax = canv -> GetUymax();
  double ylength = ymax - ymin;

  TLatex * tex = new TLatex();
  tex -> SetTextSize(0.05);
  tex -> SetTextFont(42);
  tex -> SetTextColor(kBlack);
  tex -> DrawLatex(xmin      , ymin + 1.03 * ylength, "Timing of HBHE RecHits: run 237068");
  // tex -> DrawLatex(xmin + 0.5, ymin + 0.20 * ylength, "Trigger: HLT_L1Tech_HBHEHO_totalOR_v5" );
  tex -> DrawLatex(xmin + 0.5, ymin + 0.20 * ylength, "Trigger: HLT_L1SingleMuOpen_v6" );
  
  TPaveStats * stats = (TPaveStats*) prof -> FindObject("stats");
  stats -> SetY2NDC(0.88);
  stats -> SetY1NDC(0.64);
  stats -> SetX2NDC(0.88);
  stats -> SetX1NDC(0.52);

  canv -> SaveAs("hbhe_timing_vs_phi_muonTrigger.pdf");

  double amplitude_in_ts = func -> GetParameter(1);
  double amplitude_in_ns = amplitude_in_ts * 25.;
  double amplitude_in_m  = amplitude_in_ns * 0.3;
  std::cout << "Amplitude in TS = " << amplitude_in_ts << std::endl;
  std::cout << "Amplitude in ns = " << amplitude_in_ns << std::endl;
  std::cout << "Amplitude in m  = " << amplitude_in_m  << std::endl;
  std::cout << "2x amplitude in m = " << 2. * amplitude_in_m  << std::endl;

}
