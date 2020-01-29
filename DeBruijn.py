# -*- coding: utf-8 -*-
"""
Created on Fri Oct 25 16:04:15 2019

@author: 陈焯阳
"""

def de_bruijn_ize(st, k):
    edges = []
    nodes = set()
    for i in range(len(st)- k + 1):
        edges.append((st[i:i+k-1], st[i+1:i+k]))
        nodes.add(st[i:i+k-1])
        nodes.add(st[i+1:i+k])
    return nodes, edges
'''
nodes, edges = de_bruijn_ize('ACGCGTCG', 3)
print(nodes)
print(edges)

def visualize_de_bruijn(st, k):
    nodes, edges = de_bruijn_ize(st, k)
    dot_str = 'diagraph "De Bruijn graph" {\n'
    for node in nodes:
        dot_str += '  %s [label="%s"] ;\n' % (node, node)
    for src, dst in edges:
        dot_str += '  %s -> %s ;\n' % (src, dst)
    return dot_str + '}\n'

import os
os.environ["PATH"] += os.pathsep + 'C:/Program Files (x86)/Graphviz2.38/bin'
dbg = visualize_de_bruijn('ACGCGTCG', 3)
%load_ext gvmagic
%dotstr visualize_de_bruijn('ACGCGTCG', 3)
'''