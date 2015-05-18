import ROOT as r
from collections import OrderedDict
from array import array

# ===============================
# Configurables
# ===============================
digiName = "HBHEc"
fileName = "output/RunAnalysis_20150420_SuperPointingMuon.root"
outFileName = 'RunAnalysis_%s_SuperPointingMuon.pdf'%digiName
outDir = "~/www/hcal/20150420_SuperPointingMuon/"

# ===============================
# some Dictionaries
# ===============================
iphiRanges = {	"HBHE": "all i#phi",
		"HBHEa": "3 #leq i#phi #leq 26",
		"HBHEb": "27 #leq i#phi #leq 50",
		"HBHEc": "57 #leq i#phi #leq 72 or 1 #leq i#phi #leq 2",
		}
entryThresholds = {
		"HBHE": (2000.,2000.),
		"HBHEa": (2000.,2000.),
		"HBHEb": (2000.,2000.),
		"HBHEc": (2000.,2000.),
		}



iphiRange = iphiRanges[digiName]
entryThreshold = entryThresholds[digiName]

inFile = r.TFile(fileName,"READ")
hists = { key.GetName().split("_")[-1]: [inFile.Get("_".join(key.GetName().split("_")[:-2]+["plusPhi",key.GetName().split("_")[-1]] ) ),inFile.Get("_".join(key.GetName().split("_")[:-2]+["minusPhi",key.GetName().split("_")[-1]] ) )] for key in r.gDirectory.GetListOfKeys() if key.GetName().split("_")[0] == digiName }

c = r.TCanvas("c1","multipads",2000,800)
c.Divide(2,1)
c.Print(outDir+outFileName+"[")

upperMeanValues = [ ]
upperErrors = [ ]
upperRunNumbers = [ ]
lowerMeanValues = [ ]
lowerErrors = [ ]
lowerRunNumbers = [ ]
for key,hists in hists.iteritems():
	if hists[0].GetEntries() == 0 and hists[1].GetEntries() == 0: continue
	print "RunNumber %s Hist Entries: %s, %s"%(key,hists[0].GetEntries(),hists[1].GetEntries())
	c.cd(1)
	hists[0].SetStats(0)
	hists[0].SetTitle("%s, %s, #phi > 0, Run Number %s, Mean Timing = %s ; RecHit Timing ; i#phi"%(digiName,iphiRange,key,hists[0].GetMean(1)))
	hists[0].Draw("colz")
	c.cd(2)
	hists[1].SetStats(0)
	hists[1].SetTitle("%s, %s, #phi < 0, Run Number %s, Mean Timing = %s ; RecHit Timing ; i#phi"%(digiName,iphiRange,key,hists[1].GetMean(1)))
	hists[1].Draw("colz")
	c.Print(outDir+outFileName)
	if hists[0].GetEntries() > entryThreshold[0]:
		upperRunNumbers.append(int(key))
		upperMeanValues.append(hists[0].GetMean(1))
		upperErrors.append(hists[0].GetMeanError(1))
	if hists[1].GetEntries() > entryThreshold[1]:
		lowerRunNumbers.append(int(key))
		lowerMeanValues.append(hists[1].GetMean(1))
		lowerErrors.append(hists[1].GetMeanError(1))

c.Print(outDir+outFileName+"]")

c.Clear()
c.Divide(2,1)
if len(upperRunNumbers) != 0:
	upperTimingVsRunNumber = r.TGraphErrors(len(upperRunNumbers),array("d",upperRunNumbers),array("d",upperMeanValues),array("d",[0 for i in range(len(upperRunNumbers))]),array("d",upperErrors))
else:
	upperTimingVsRunNumber = r.TGraphErrors()
c.cd(1)
upperTimingVsRunNumber.SetTitle("%s, %s, Summary, #phi > 0 ; Run Number ;  Mean Value of RecHit Timing "%(digiName,iphiRange))
upperTimingVsRunNumber.SetLineColor(3)
upperTimingVsRunNumber.Draw("AP")
c.cd(2)
if len(lowerRunNumbers) != 0:
	lowerTimingVsRunNumber = r.TGraphErrors(len(lowerRunNumbers),array("d",lowerRunNumbers),array("d",lowerMeanValues),array("d",[0 for i in range(len(lowerRunNumbers)) ]),array("d",lowerErrors))
else:
	lowerTimingVsRunNumber = r.TGraphErrors()
lowerTimingVsRunNumber.SetTitle("%s, %s, Summary, #phi < 0 ; Run Number ;  Mean Value of RecHit Timing "%(digiName,iphiRange))
lowerTimingVsRunNumber.SetLineColor(3)
lowerTimingVsRunNumber.Draw("AP")
c.Print(outDir+"Summary_"+outFileName)


