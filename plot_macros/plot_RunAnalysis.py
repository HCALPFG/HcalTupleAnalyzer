import ROOT as r
from collections import OrderedDict
from array import array

# ===============================
# Configurables
# ===============================
fileName = "output/RunAnalysis_20150420_SuperPointingMuon.root"
outFileName = 'RunAnalysis_SuperPointingMuon.pdf'
outDir = "~/www/hcal/20150420_SuperPointingMuon/"

inFile = r.TFile(fileName,"READ")
hists = { key.GetName().split("_")[-1]: [inFile.Get("_".join(key.GetName().split("_")[:-2]+["plusPhi",key.GetName().split("_")[-1]] ) ),inFile.Get("_".join(key.GetName().split("_")[:-2]+["minusPhi",key.GetName().split("_")[-1]] ) )] for key in r.gDirectory.GetListOfKeys() if key.GetName().split("_")[0] == "HBHE" }

c = r.TCanvas("c1","multipads",2000,800)
c.Divide(2,1)
c.Print(outDir+outFileName+"[")

upperMeanValues = [ ]
upperErrors = [ ]
lowerMeanValues = [ ]
lowerErrors = [ ]
runNumbers = [ ]
for key,hists in hists.iteritems():
	if hists[0].GetEntries() == 0 and hists[1].GetEntries() == 0: continue
	c.cd(1)
	hists[0].SetStats(0)
	hists[0].SetTitle("#phi > 0, Run Number %s, Mean Timing = %s ; RecHit Timing ; i#phi"%(key,hists[0].GetMean(1)))
	hists[0].Draw("colz")
	c.cd(2)
	hists[1].SetStats(0)
	hists[1].SetTitle("#phi < 0, Run Number %s, Mean Timing = %s ; RecHit Timing ; i#phi"%(key,hists[1].GetMean(1)))
	hists[1].Draw("colz")
	c.Print(outDir+outFileName)
	upperMeanValues.append(hists[0].GetMean(1))
	upperErrors.append(hists[0].GetMeanError(1))
	lowerMeanValues.append(hists[1].GetMean(1))
	lowerErrors.append(hists[1].GetMeanError(1))
	runNumbers.append(int(key))

c.Print(outDir+outFileName+"]")

c.Clear()
c.Divide(2,1)
upperTimingVsRunNumber = r.TGraphErrors(len(runNumbers),array("d",runNumbers),array("d",upperMeanValues),array("d",[0 for i in range(len(runNumbers))]),array("d",upperErrors))
c.cd(1)
upperTimingVsRunNumber.SetTitle("Summary, #phi > 0 ; Run Number ;  Mean Value of RecHit Timing ")
upperTimingVsRunNumber.SetLineColor(3)
upperTimingVsRunNumber.Draw("AP")
c.cd(2)
lowerTimingVsRunNumber = r.TGraphErrors(len(runNumbers),array("d",runNumbers),array("d",lowerMeanValues),array("d",[0 for i in range(len(runNumbers)) ]),array("d",lowerErrors))
lowerTimingVsRunNumber.SetTitle("Summary, #phi < 0 ; Run Number ;  Mean Value of RecHit Timing ")
lowerTimingVsRunNumber.SetLineColor(3)
lowerTimingVsRunNumber.Draw("AP")
c.Print(outDir+"Summary_"+outFileName)


