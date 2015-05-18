#----------------------------------------------------------------------------
# Imports
#----------------------------------------------------------------------------

import ROOT as r
import subprocess as sp
import sys, os
import argparse

#----------------------------------------------------------------------------
# Parse arguments
#----------------------------------------------------------------------------

parser = argparse.ArgumentParser(description='Wrapper for TTree::MakeClass')
parser.add_argument('-i', metavar='INPUTFILE' , dest='input_file' ,action="store", required=True, help='Input root file')
parser.add_argument('-t', metavar='TREENAME'  , dest='tree_name'  ,action="store", required=True, help='TTree name')
parser.add_argument('-c', metavar='CLASSNAME' , dest='class_name' ,action="store", required=True, help='Output class name')
args = parser.parse_args()

#----------------------------------------------------------------------------
# Get the TTree
#----------------------------------------------------------------------------

if args.input_file[0:5] == "/eos/" :
    input_file_name = "root://eoscms/" + args.input_file
else:
    input_file_name = args.input_file

input_file = r.TFile.Open (input_file_name)
input_tree = input_file.Get(args.tree_name)

#----------------------------------------------------------------------------
# Make the class
#----------------------------------------------------------------------------

status = input_tree.MakeClass(args.class_name)

if not status == 0: 
    print "Error! MakeClass status =", status
    print "Bailing."
    sys.exit()
else:
    print "Success!  Made a class from tree:", args.tree_name, "in file:", args.input_file

#----------------------------------------------------------------------------
# Move the file somewhere useful
#----------------------------------------------------------------------------

os.system ( "perl -pi -e 's/#define HcalTupleTree_h/#define HcalTupleTree_h\nusing namespace std;/g' " + args.class_name + ".h" )
os.system ( "mv " + args.class_name + ".h include/" )
os.system ( "mv " + args.class_name + ".C src/" )

