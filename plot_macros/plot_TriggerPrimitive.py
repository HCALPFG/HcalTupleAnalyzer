
import ROOT
from PlotParser import parser
import math

def decorate(hist):
	wordKey = {1: "<",2: ">"}
	hist.SetStats(0)
	name = hist.GetName()
	lumiSectionIndex = int(name.split('_')[-2])
	iphi = int(name.split('_')[-1])
	title = "LumiSection %s 400, i#phi = %s ; Emulated TP Et ; Data TP Et"%(wordKey[lumiSectionIndex],iphi)
	hist.SetTitle(title)


ROOT.gROOT.SetBatch(ROOT.kTRUE)

args = parser.parse_args()

inFileName = args.inputPath
outFileName = args.outputPath

inputFile = ROOT.TFile(inFileName,"READ")
histNames = [k.GetName() for k in inputFile.GetListOfKeys()]
hists = [ inputFile.Get(histName) for histName in histNames if "lumi" not in histName]

print "Total Number of Hist: %s"%len(hists)
c = ROOT.TCanvas()
c.SetLogz()
c.Print(outFileName+"[")
for i,hist in enumerate(hists):
	decorate(hist)
	hist.Draw("colz")
	c.Print(outFileName)
c.Print(outFileName+"]")
# c.SaveAs(outFileName)

