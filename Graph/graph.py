# -*- coding: utf-8 -*-
"""
Created on Mon Mar 18 20:34:23 2024

@author: wangj
"""
from graphviz import Digraph
import os
from PIL import Image
import matplotlib.pyplot as plt
import pandas as pd

# read graphdata
#   myorder   /    order   /    yuan 
dfn = pd.read_csv("data/order/Graph data node.csv", skiprows=0, encoding='unicode_escape')
dfe = pd.read_csv("data/order/Graph data edge.csv", skiprows=0, encoding='unicode_escape')

dfn['rank'] = dfn['rank'].astype('str')
dfn['id'] = dfn['id'].astype('str')
dfn['name'] = dfn['name'].astype('str')
dfe['id1'] = dfe['id1'].astype('str')
dfe['id2'] = dfe['id2'].astype('str')

# DG
#   dot   /    circo   /    neato   /    fdp   /    osage   /    twopi    /   sfdp
g = Digraph('G',engine='circo', strict = True)
g.attr(rankdir='LR', size='20,20')
#myorder
g.attr('node', fontsize='70',width='0.1')
g.attr('edge', penwidth='6', arrowsize = '3')
#order
# g.attr('node', fontsize='40',width='0.1')
# g.attr('edge', penwidth='2', arrowsize = '3')
#yuan
# g.attr('node', fontsize='40',width='0.1')
# g.attr('edge', penwidth='3', arrowsize = '3')
g.attr(compound='true')

# nodes
for row_index, row in dfn.iterrows():
    pos = row['xy']
    pos = pos.replace(':', ',')
    g.node(row['name'], style="filled", color= row['color16'], rank = row['rank'], pos=pos)
    # g.node(row['name'], style="filled", color= row['color16'] ,rank = row['rank'], pos=pos)
    # g.node(row['name'], style="filled", color= row['color16'] ,rank = row['rank'])#, pos=row['xy'])
    # G.add_node(row['name2'], fontname="Times-Roman", style="filled", color= row['color16'], pos="x,y(!)")
    # G.add_node(cell)
    # G.add_node(cell)
    # G.add_node(cell)

# edges
for row_index, row in dfe.iterrows():
    if row["dir"] == 'both':
        g.edge(row['origin'],row['target'], dir = row["dir"], color = "blue")
    else:
        g.edge(row['origin'],row['target'], dir = row["dir"], color = "black")
        
    # if row["dir"] == 'both':
    #     g.edge(row['id1'],row['id2'], dir = row["dir"], color = "blue")
    # else:
    #     g.edge(row['id1'],row['id2'], dir = row["dir"], color = "black")


# output
print(g.source)  
g.render('output/graphviz.gv', format='png', view=True)  

# show
img = Image.open("output/graphviz.gv.png")
plt.imshow(img)
plt.axis('off') # off
plt.show()
