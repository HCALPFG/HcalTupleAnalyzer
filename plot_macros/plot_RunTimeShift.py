
import ROOT
from PlotParser import parser

ROOT.gROOT.SetBatch(ROOT.kTRUE)

args = parser.parse_args()

inFileName = args.inputPath
outFileName = args.outputPath

# Configurables
# summaryHistNames = ["RecHitTiming_vs_RunNumber","AvgTiming_vs_RunNumber"]
histTitles = {
		"RecHitTiming_vs_RunNumber": " ; Run Number ; Average RecHitTiming [ns]",
		"AvgTiming_vs_RunNumber": " ; Run Number ; Average Energy-Average-Timing [TS]",
		# "HBRecHitTiming_vs_RunNumber":  " HB ; Run Number ; Average RecHitTiming [ns]",
		# "HBAvgTiming_vs_RunNumber": " HB ; Run Number ; Average Energy-Average-Timing [TS]",
		# "HERecHitTiming_vs_RunNumber": " HE ; Run Number ; Average RecHitTiming [ns]",
		# "HEAvgTiming_vs_RunNumber": " HE ; Run Number ; Average Energy-Average-Timing [TS]",
		}

inputFile = ROOT.TFile(inFileName,"READ")
# histNames = [k.GetName() for k in inputFile.GetListOfKeys()]
# hists = [ inputFile.Get(histName) for histName in histNames if "HBHE" in histName]
# 
# print "Total Number of Hist: %s"%len(hists)
# c = ROOT.TCanvas()
# c.Print(outFileName+"[")
# for i,hist in enumerate(hists):
# 	if not ((i & 1000) == 0): continue
# 	# print i
# 	hist.SetStats(0)
# 	hist.Draw()
# 	c.Print(outFileName)
# c.Print(outFileName+"]")
# c.SaveAs(outFileName)

# summaryHists = [inputFile.Get(summaryHistName) for summaryHistName in histTitles ]
c = ROOT.TCanvas()
summaryFilePath = outFileName.replace(".pdf","_summary.pdf")
c.Print(summaryFilePath+"[")
# for summaryHist in summaryHists:
for summaryHistName,title in histTitles.iteritems():
	summaryHist = inputFile.Get(summaryHistName)
	summaryHist.SetStats(0)
	summaryHist.SetTitle(title)
	summaryHist.Draw()
	c.Print(summaryFilePath)
c.Print(summaryFilePath+"]")
