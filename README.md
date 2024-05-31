  # DAG

## What is this repository for?
DAG is a TOOL for automatic acquisition of complex stratigraphic order from boreholes through topological relationship graphs and stratigraphic poses.



## How do I get set up?

Please download the .zip file or run

```
git clone https://github.com/sherryfive/DAG.git
```

in your command line.

***Required:***
- C++ Compiler: [VS2022](https://visualstudio.microsoft.com/zh-hans/vs/), [Qt 5.15.2](https://www.qt.io/blog/qt-5.15.2-released).
- C++ packages: PCL 1.9.0
- Python: >= 3.11.8
- python packages: scipy, numpy, sys, skimage, graphviz, PIL, matplotlib, pandas

## Usage
There are two main folders in this repository: [DAGC](https://github.com/sherryfive/DAG/blob/main/DAGC/) and [Graph](https://github.com/sherryfive/DAG/blob/main/Graph/).

### DAGC

This is a solution written in C++. This folder contains the code, data, and results for automatically obtaining stratigraphic sequences.

- Code: ***.h*** and ***.cpp*** files in [DAGC](https://github.com/sherryfive/DAG/blob/main/DAGC/). Compile with VS2022 and Qt 5.15.2.
- Data: ***BH-5000-myorder.csv***, ***BH-5000-order.csv***, and ***BH-5000-YUAN.csv*** in the [vipfile](https://github.com/sherryfive/DAG/blob/main/DAGC/vipfile/) folder.
- Result: ***Graph data node.csv*** and ***Graph data edge.csv*** in the [vipfile](https://github.com/sherryfive/DAG/blob/main/DAGC/vipfile/) folder.

### Graph

This folder contains the data, code, and results used to draw the TRG model.

- Code: [graph.py](https://github.com/sherryfive/DAG/blob/main/Graph/graph.py), which is to show the TRG model.
- Data: the results of DAGC in the [data](https://github.com/sherryfive/DAG/blob/main/Graph/data/) folder.
- Result: graphviz.gv.png in the [output](https://github.com/sherryfive/DAG/blob/main/Graph/output/) folder.

## Who do I talk to?
Jiangmei Wang, Northeastern University, wangjiangmei_gs@163.com


  
