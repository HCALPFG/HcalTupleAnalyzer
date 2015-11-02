
import ROOT
from PlotParser import parser

ROOT.gROOT.SetBatch(ROOT.kTRUE)

args = parser.parse_args()

inFileName = args.inputPath
outFileName = args.outputPath

inputFile = ROOT.TFile(inFileName,"READ")
histNames = [k.GetName() for k in inputFile.GetListOfKeys()] 
histNames.sort()

print "Total Number of Hist: %s"%len(histNames)
c = ROOT.TCanvas()
c.Print(outFileName+"[")
for histName in histNames:
	hist = inputFile.Get(histName)
	hist.SetStats(0)
	# hist.GetYaxis().SetRangeUser(0.,1.2*hist.GetMaximum())
	# hist.SetTitle(hist.GetName().replace("_"," ").replace("EndCap","Central")+" ; TS ; Average fC per rechit")
	hist.Draw("colz")
	c.Print(outFileName)
c.Print(outFileName+"]")
