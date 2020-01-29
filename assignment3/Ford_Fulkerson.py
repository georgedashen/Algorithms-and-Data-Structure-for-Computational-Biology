# -*- coding: utf-8 -*-
"""
Created on Thu Dec  5 13:01:29 2019

@author: 陈焯阳
"""
import random
import DFS

# what I changed in the code are:
# 1. change the "yield" current_path to "return";
# 2. a forth argument "flow" is needed to keep track of residual network
# 3. a condition that "capacity > 0" is added to find paths based on residuals
def dfs_path(graph, start, end, flow):
    visited = set()
    #pred = {}
    stack = [(start, [start])]
    while stack:
        (vertex, current_path) = stack.pop()        
        if vertex not in visited:
            if vertex == end:
                return current_path
            visited.add(vertex)
            temp = graph.get_edges(vertex)
            random.shuffle(temp)
            for next_v in temp: 
                #####################################
                if findFlow(vertex, next_v, flow).capacity:
                #####################################
                    stack.append((next_v, current_path + [next_v]))

# If a path is found, update the residual network
# and return the augment flow added to the destination "t", which is the miniflow of the path
def updateFlow(path, flow):
    minflow = 10000
    # to find the minimum flow of current flow
    for i in range(len(path)-1):
        if findFlow(path[i],path[i+1],flow).capacity < minflow:
            minflow = findFlow(path[i],path[i+1],flow).capacity
    # reduce the current capacity with the minimum flow            
    for i in range(len(path)-1):
            findFlow(path[i],path[i+1],flow).capacity -= minflow
            findFlow(path[i+1],path[i],flow).capacity += minflow
            
    return minflow

# find the flow according to start and end
def findFlow(start, end, flow):
    for i in flow:
        if i.start == start and i.end == end:
            return i
    return None

##############################################################
## For the purpose of test, not necessary

# reset the residual network with initial capacities
def resetFlow(flow):
    for i,edge in enumerate(flow):
        edge.capacity = InitCap[i]

# Display the residual network
def displayFlow(flow):
    for i in flow:
        print("%s -> %s : %d" %(i.start, i.end, i.capacity))
    print("\n")
##############################################################
	
## Example from lecture to test Ford-Fulkerson Algorithm
## Maxflow should be 19
'''
# The graph is used to store the topological structure
G = Graph()
# The flow is used to store direction and residual network of edges
# A list of edges defined by TAs
Flow = []
G.add_node(Node("s"))
G.add_node(Node("t"))
G.add_node(Node("A"))
G.add_node(Node("B"))
G.add_node(Node("C"))
G.add_node(Node("D"))

G.add_edge(Edge("s","A",10))
G.add_edge(Edge("s","B",10))
G.add_edge(Edge("A","B",2))
G.add_edge(Edge("A","C",4))
G.add_edge(Edge("A","D",8))
G.add_edge(Edge("B","D",9))
G.add_edge(Edge("D","C",6))
G.add_edge(Edge("C","t",10))
G.add_edge(Edge("D","t",10))

# For each edge, store itself with initial capacity
Flow.append(Edge("s","A",10))
# and its reverse direction with capacity 0
Flow.append(Edge("A","s",0))

Flow.append(Edge("s","B",10))
Flow.append(Edge("B","s",0))

Flow.append(Edge("A","B",2))
Flow.append(Edge("B","A",0))

Flow.append(Edge("A","C",4))
Flow.append(Edge("C","A",0))

Flow.append(Edge("A","D",8))
Flow.append(Edge("D","A",0))

Flow.append(Edge("B","D",9))
Flow.append(Edge("D","B",0))

Flow.append(Edge("D","C",6))
Flow.append(Edge("C","D",0))

Flow.append(Edge("C","t",10))
Flow.append(Edge("t","C",0))

Flow.append(Edge("D","t",10))
Flow.append(Edge("t","D",0))

#InitCap stores the starting capacities of network
InitCap = []
for i in Flow:
    InitCap.append(i.capacity)

maxflow = 0
add = 0


# traverse the network, find paths and update network until no paths found

while True:
    Path = dfs_path(G,"s","t", Flow) #find a path available
    if Path == None:
        break #if no path found, reach maximum flow
    add = updateFlow(Path, Flow) # update the residuals and return the miniflow of that path
    maxflow += add #add augment flow to the destination
    #displayFlow(Flow)

print(maxflow)
'''

