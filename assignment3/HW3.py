# -*- coding: utf-8 -*-
"""
Created on Tue Dec  3 14:19:05 2019

@author: 陈焯阳
"""

import DFS
import Ford_Fulkerson

## input with number of nodes and their connections
n = 3
links = [(1,1),(1,2),(2,3),(3,2)]

## an empty list to store direction and residual network of edges
flow = []

def networkSetup(g, flow, n, links):

    g.add_node(Node("s"))
    g.add_node(Node("t"))
    
    for i in range(1,n+1):
        g.add_node(Node(str(i)))
        g.add_node(Node(str(i+n)))
        
        g.add_edge(Edge("s",str(i),1))
        g.add_edge(Edge("t",str(i+n),1))
        
        flow.append(Edge("s",str(i),1))
        flow.append(Edge(str(i),"s",0))
        flow.append(Edge(str(i+n),"t", 1))
        flow.append(Edge("t",str(i+n), 0))
        
    for i in range(len(links)):
        g.add_edge(Edge(str(links[i][0]),str(links[i][1]+n),1))
        flow.append(Edge(str(links[i][0]),str(links[i][1]+n),1))
        flow.append(Edge(str(links[i][1]+n),str(links[i][0]),0))


## Find connection of network
g = Graph()
networkSetup(g, flow, n, links)


while True:
    path = dfs_path(g,"s","t", flow)
    if path == None:
        break
    updateFlow(path, flow)
    #displayFlow(flow)

for i in range(1,n+1):
    for edge in flow:
        if edge.start == str(i) and edge.capacity == 0:
            print("%s %d" %(edge.start, int(edge.end)-n))
 
###############################################################################
# Tradition way to traverse the network to find the connections
def get_path(graph, start, end, flow):
    visited = set()
    stack = [(start, [start])]
    while stack:
        (vertex, current_path) = stack.pop()        
        if vertex not in visited or vertex == 't':
            if vertex == end:
                yield current_path
            visited.add(vertex)
            temp = graph.get_edges(vertex)
            random.shuffle(temp)
            for next_v in temp: 
                if findFlow(vertex, next_v, flow).capacity == 0:
                    stack.append((next_v, current_path + [next_v]))

gen = get_path(g, "s", "t", flow)
connection = []
for i in gen:
    connection.append(i)
# all the paths with final connection are stored
###############################################################################

    
    
    
    
    
    
    