
import ROOT
from PlotParser import parser

ROOT.gROOT.SetBatch(ROOT.kTRUE)
parser.add_argument('-s', metavar="select", dest='select',action="store" , required=True, help='prefix for selecting plots',type=str)
parser.add_argument('-d', metavar="option", dest='option',action="store" , required=True, help='draw option',type=str)

args = parser.parse_args()

inFileName = args.inputPath
outFileName = args.outputPath
hist_prefix = args.select
drawOption = args.option

inputFile = ROOT.TFile(inFileName,"READ")
histNames = [k.GetName() for k in inputFile.GetListOfKeys() if hist_prefix in k.GetName() ] 
hists =  [ inputFile.Get(histName) for histName in histNames ]

print "Total Number of Hist: %s"%len(hists)
c = ROOT.TCanvas()
c.Print(outFileName+"[")
for i,hist in enumerate(hists):
	hist.SetStats(0)
	hist.GetYaxis().SetRangeUser(0.,1.2*hist.GetMaximum())
	# hist.SetTitle(hist.GetName().replace("_"," ").replace("EndCap","Central")+" ; TS ; Average fC per rechit")
	hist.Draw(drawOption)
	c.Print(outFileName)
c.Print(outFileName+"]")
