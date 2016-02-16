# HcalTupleAnalyzer
This code is to analyze the output of HcalTupleMaker. 
You should add your own analysis to the macros/ folder and run it with run.py

Simple Usage: When you have only one type of input files in your analysis
```
python run.py macros/analysisClass_HFPhaseScan.C config/input_lists/simple_list.txt config/tree_lists/treelist.txt output.root
```

2-input type Usage: When you have 2 type of input files, e.g vme_ouput.root and utca_output.root
```
python run.py macros/analysisClass_uHBHECommissioning.C config/input_lists/main_input.txt config/tree_lists/tree_list.txt output.root
```
