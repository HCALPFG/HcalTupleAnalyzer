
import argparse

parser = argparse.ArgumentParser(description='Make an input list')

parser.add_argument('-i', metavar="inputPath", dest='inputPath',action="store" , required=True, help='Input file path',type=str)
parser.add_argument('-o', metavar="output", dest='outputPath',action="store" , required=True, help='Output file path',type=str)
