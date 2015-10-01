
import ROOT
from PlotParser import parser

ROOT.gROOT.SetBatch(ROOT.kTRUE)

args = parser.parse_args()

inFileName = args.inputPath
outFileName = args.outputPath

inputFile = ROOT.TFile(inFileName,"READ")
histNames = [k.GetName() for k in inputFile.GetListOfKeys()]
hists = [ inputFile.Get(histName) for histName in histNames if "HBHE" in histName]

print "Total Number of Hist: %s"%len(hists)
c = ROOT.TCanvas()
c.Print(outFileName+"[")
for i,hist in enumerate(hists):
	if not ((i & 1000) == 0): continue
	# print i
	hist.SetStats(0)
	hist.Draw()
	c.Print(outFileName)
c.Print(outFileName+"]")
# c.SaveAs(outFileName)

summaryHist = inputFile.Get("RecHitTiming_vs_RunNumber")
c = ROOT.TCanvas()
summaryHist.SetStats(0)
summaryHist.SetTitle(" ; Run Number ; Average RecHit Timing [ns]")
summaryHist.Draw()
c.SaveAs(outFileName.replace(".pdf","_summary.pdf"))
