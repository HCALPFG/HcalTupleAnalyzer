import ROOT as r
import copy

# r.gStyle.SetOptStat(1)
# r.gStyle.SetOptTitle(0)

fileName = "output/Collisions_Method0_246958.root"
outputPath = "~/www/hcal/HCALPFG/20150604_Collisions_246958/Method0/"

histNames = [
	"energy",
	"time",
	"time_vs_energy",
	"eta_vs_phi",
	"ieta_vs_iphi",
	"eta_vs_phi_TimingCut",
	"ieta_vs_iphi_TimingCut",
	"ieta_vs_iphi_averageTime_depth1",
	"ieta_vs_iphi_averageTime_depth2",
	"ieta_vs_iphi_averageTime_depth3",
		]

Title = "HBHEDigi Energy > 5 GeV, Run Number 246958, Method 0"

titles = {
	"energy":Title+" ; Energy [GeV] ; ",
	"time":Title+" ; RecHitTime [ns]  ; ",
	"time_vs_energy":Title+" ; RecHitTime [ns] ; Energy [GeV] ",
	"eta_vs_phi":Title+" ; #eta ; #phi ",
	"ieta_vs_iphi":Title+" ; i#eta ; i#phi ",
	"eta_vs_phi_TimingCut":Title+", RecHitTime > 0 ns ; #eta ; #phi ",
	"ieta_vs_iphi_TimingCut":Title+", RecHitTime > 0 ns ; i#eta ; i#phi ",
	"ieta_vs_iphi_averageTime_depth1":Title+", Depth 1 ; i#eta ; i#phi ",
	"ieta_vs_iphi_averageTime_depth2":Title+", Depth 2 ; i#eta ; i#phi ",
	"ieta_vs_iphi_averageTime_depth3":Title+", Depth 3 ; i#eta ; i#phi ",
		}


histFile = r.TFile(fileName,"READ")
canvas = r.TCanvas()

for histName in histNames:
	save_name = histName+".pdf"
	hist = copy.deepcopy(histFile.Get(histName))
	hist.SetTitle(titles[histName])
	if "vs" not in histName:
		hist.SetFillStyle(3004)
		canvas.SetLogy(1)
		my_max = 1.2*hist.GetMaximum()
		hist.SetMaximum(my_max)
		hist.Draw()
	else:
		canvas.SetLogy(0)
		hist.Draw("colz")
	canvas.Print(outputPath+save_name)

	
	

